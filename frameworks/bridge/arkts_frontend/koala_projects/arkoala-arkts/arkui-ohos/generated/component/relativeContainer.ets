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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookRelativeContainerAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Dimension } from "./units"
import { Resource } from "global.resource"
import { Axis } from "./enums"
import { RelativeContainerModifier } from "./../RelativeContainerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
export class ArkRelativeContainerPeer extends ArkCommonMethodPeer {
    attributeSet?: RelativeContainerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRelativeContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RelativeContainer_construct(peerId, flags)
        const _peer  = new ArkRelativeContainerPeer(_peerPtr, peerId, 'RelativeContainer', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRelativeContainerOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._RelativeContainerInterface_setRelativeContainerOptions(this.peer.ptr)
    }
    setGuideLineAttribute(value: Array<GuideLineStyle> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : GuideLineStyle = valueTmpValue[valueTmpValueCounterI]
                GuideLineStyle_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_setGuideLine(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarrierAttribute(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (TypeChecker.isArray_BarrierStyle(valueTmpValue)) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Array<BarrierStyle>
                thisSerializer.writeInt32((valueTmpValueForIdx0.length).toInt())
                for (let valueTmpValueForIdx0CounterI = 0; valueTmpValueForIdx0CounterI < valueTmpValueForIdx0.length; valueTmpValueForIdx0CounterI++) {
                    const valueTmpValueForIdx0TmpElement : BarrierStyle = valueTmpValueForIdx0[valueTmpValueForIdx0CounterI]
                    BarrierStyle_serializer.write(thisSerializer, valueTmpValueForIdx0TmpElement)
                }
            } else if (TypeChecker.isArray_LocalizedBarrierStyle(valueTmpValue)) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Array<LocalizedBarrierStyle>
                thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                    const valueTmpValueForIdx1TmpElement : LocalizedBarrierStyle = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                    LocalizedBarrierStyle_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_setBarrier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setRelativeContainerOptions(): this {
        throw new Error("Unimplemented method setRelativeContainerOptions")
    }
    guideLine(value: Array<GuideLineStyle> | undefined): this {
        throw new Error("Unimplemented method guideLine")
    }
    barrier(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): this {
        throw new Error("Unimplemented method barrier")
    }
    attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRelativeContainerStyle extends ArkCommonMethodStyle implements RelativeContainerAttribute {
    guideLine_value?: Array<GuideLineStyle> | undefined
    barrier_value?: Array<BarrierStyle> | undefined
    attributeModifier_value?: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined
    setRelativeContainerOptions(): this {
        return this
    }
    guideLine(value: Array<GuideLineStyle> | undefined): this {
        return this
    }
    barrier(value: Array<BarrierStyle> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRelativeContainerComponent extends ArkCommonMethodComponent implements RelativeContainerAttribute {
    getPeer(): ArkRelativeContainerPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkRelativeContainerPeer)
    }
    public setRelativeContainerOptions(): this {
        if (this.checkPriority("setRelativeContainerOptions")) {
            this.getPeer()?.setRelativeContainerOptionsAttribute()
            this.applyOptionsFinish('RelativeContainerAttribute');
            return this
        }
        return this
    }
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        if (this.checkPriority("guideLine")) {
            const value_casted = value as (Array<GuideLineStyle> | undefined)
            this.getPeer()?.setGuideLineAttribute(value_casted)
            return this
        }
        return this
    }
    public barrier(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): this {
        if (this.checkPriority("barrier")) {
            const value_casted = value as (Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined)
            this.getPeer()?.setBarrierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookRelativeContainerAttributeModifier(this, value);
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
export function RelativeContainerImpl(
    @memo
    style: ((attributes: RelativeContainerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRelativeContainerComponent>((): ArkRelativeContainerComponent => {
        return new ArkRelativeContainerComponent()
    })
    NodeAttach<ArkRelativeContainerPeer>((): ArkRelativeContainerPeer => ArkRelativeContainerPeer.create(receiver), (peer: ArkRelativeContainerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class BarrierStyle_serializer {
    public static write(buffer: SerializerBase, value: BarrierStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(valueHolderForDirection.valueOf())
        const valueHolderForReferencedId  = value.referencedId
        valueSerializer.writeInt32((valueHolderForReferencedId.length).toInt())
        for (let valueHolderForReferencedIdCounterI = 0; valueHolderForReferencedIdCounterI < valueHolderForReferencedId.length; valueHolderForReferencedIdCounterI++) {
            const valueHolderForReferencedIdTmpElement : string = valueHolderForReferencedId[valueHolderForReferencedIdCounterI]
            valueSerializer.writeString(valueHolderForReferencedIdTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): BarrierStyle {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const directionTmpResult : BarrierDirection = BarrierDirection.fromValue(valueDeserializer.readInt32())
        const referencedIdTmpBufLength : int32 = valueDeserializer.readInt32()
        let referencedIdTmpBuf : Array<string> = new Array<string>(referencedIdTmpBufLength)
        for (let referencedIdTmpBufBufCounterI = 0; referencedIdTmpBufBufCounterI < referencedIdTmpBufLength; referencedIdTmpBufBufCounterI++) {
            referencedIdTmpBuf[referencedIdTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const referencedIdTmpResult : Array<string> = referencedIdTmpBuf
        let value : BarrierStyle = ({id: idTmpResult, direction: directionTmpResult, referencedId: referencedIdTmpResult} as BarrierStyle)
        return value
    }
}

export class LocalizedBarrierStyle_serializer {
    public static write(buffer: SerializerBase, value: LocalizedBarrierStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForLocalizedDirection  = value.localizedDirection
        valueSerializer.writeInt32(valueHolderForLocalizedDirection.valueOf())
        const valueHolderForReferencedId  = value.referencedId
        valueSerializer.writeInt32((valueHolderForReferencedId.length).toInt())
        for (let valueHolderForReferencedIdCounterI = 0; valueHolderForReferencedIdCounterI < valueHolderForReferencedId.length; valueHolderForReferencedIdCounterI++) {
            const valueHolderForReferencedIdTmpElement : string = valueHolderForReferencedId[valueHolderForReferencedIdCounterI]
            valueSerializer.writeString(valueHolderForReferencedIdTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedBarrierStyle {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const localizedDirectionTmpResult : LocalizedBarrierDirection = LocalizedBarrierDirection.fromValue(valueDeserializer.readInt32())
        const referencedIdTmpBufLength : int32 = valueDeserializer.readInt32()
        let referencedIdTmpBuf : Array<string> = new Array<string>(referencedIdTmpBufLength)
        for (let referencedIdTmpBufBufCounterI = 0; referencedIdTmpBufBufCounterI < referencedIdTmpBufLength; referencedIdTmpBufBufCounterI++) {
            referencedIdTmpBuf[referencedIdTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const referencedIdTmpResult : Array<string> = referencedIdTmpBuf
        let value : LocalizedBarrierStyle = ({id: idTmpResult, localizedDirection: localizedDirectionTmpResult, referencedId: referencedIdTmpResult} as LocalizedBarrierStyle)
        return value
    }
}

export class GuideLinePosition_serializer {
    public static write(buffer: SerializerBase, value: GuideLinePosition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            if (valueHolderForStartTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartTmpValueForIdx0  = valueHolderForStartTmpValue as string
                valueSerializer.writeString(valueHolderForStartTmpValueForIdx0)
            } else if (valueHolderForStartTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStartTmpValueForIdx1  = valueHolderForStartTmpValue as number
                valueSerializer.writeNumber(valueHolderForStartTmpValueForIdx1)
            } else if (valueHolderForStartTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStartTmpValueForIdx2  = valueHolderForStartTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStartTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            if (valueHolderForEndTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndTmpValueForIdx0  = valueHolderForEndTmpValue as string
                valueSerializer.writeString(valueHolderForEndTmpValueForIdx0)
            } else if (valueHolderForEndTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForEndTmpValueForIdx1  = valueHolderForEndTmpValue as number
                valueSerializer.writeNumber(valueHolderForEndTmpValueForIdx1)
            } else if (valueHolderForEndTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForEndTmpValueForIdx2  = valueHolderForEndTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForEndTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GuideLinePosition {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : Dimension | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startTmpBuf_ : string | number | Resource | undefined
            if (startTmpBuf_UnionSelector == (0).toChar()) {
                startTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (startTmpBuf_UnionSelector == (1).toChar()) {
                startTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (startTmpBuf_UnionSelector == (2).toChar()) {
                startTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startTmpBuf_ has to be chosen through deserialisation.")
            }
            startTmpBuf = (startTmpBuf_ as string | number | Resource)
        }
        const startTmpResult : Dimension | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : Dimension | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endTmpBuf_ : string | number | Resource | undefined
            if (endTmpBuf_UnionSelector == (0).toChar()) {
                endTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (endTmpBuf_UnionSelector == (1).toChar()) {
                endTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (endTmpBuf_UnionSelector == (2).toChar()) {
                endTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endTmpBuf_ has to be chosen through deserialisation.")
            }
            endTmpBuf = (endTmpBuf_ as string | number | Resource)
        }
        const endTmpResult : Dimension | undefined = endTmpBuf
        let value : GuideLinePosition = ({start: startTmpResult, end: endTmpResult} as GuideLinePosition)
        return value
    }
}
export class GuideLineStyle_serializer {
    public static write(buffer: SerializerBase, value: GuideLineStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(valueHolderForDirection.valueOf())
        const valueHolderForPosition  = value.position
        GuideLinePosition_serializer.write(valueSerializer, valueHolderForPosition)
    }
    public static read(buffer: DeserializerBase): GuideLineStyle {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const directionTmpResult : Axis = Axis.fromValue(valueDeserializer.readInt32())
        const positionTmpResult : GuideLinePosition = GuideLinePosition_serializer.read(valueDeserializer)
        let value : GuideLineStyle = ({id: idTmpResult, direction: directionTmpResult, position: positionTmpResult} as GuideLineStyle)
        return value
    }
}

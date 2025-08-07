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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Dimension } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { Axis } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkRelativeContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setBarrierAttribute(value: Array<BarrierStyle> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : BarrierStyle = valueTmpValue[valueTmpValueCounterI]
                BarrierStyle_serializer.write(thisSerializer, valueTmpValueTmpElement)
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
    guideLine(value: Array<GuideLineStyle> | undefined): this {
        throw new Error("Unimplemented method guideLine")
    }
    barrier(value: Array<BarrierStyle> | undefined): this {
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
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        return this
    }
    public barrier(value: Array<BarrierStyle> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
            this.getPeer()?.setGuideLineAttribute(value_casted)
            return this
        }
        return this
    }
    public barrier(value: Array<BarrierStyle> | undefined): this {
        if (this.checkPriority("barrier")) {
            const value_casted = value as (Array<BarrierStyle> | undefined)
            this.getPeer()?.setBarrierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function RelativeContainer(
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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RelativeContainerModifier extends CommonMethodModifier implements RelativeContainerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _guideLine_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _guideLine_0_0value?: Array<GuideLineStyle> | undefined
    _barrier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barrier_0_0value?: Array<BarrierStyle> | undefined
    applyModifierPatch(peer: ArkRelativeContainerPeer): void {
        super.applyModifierPatch(peer)
        if (this._guideLine_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._guideLine_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGuideLineAttribute((this._guideLine_0_0value as Array<GuideLineStyle> | undefined));
                    this._guideLine_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._guideLine_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._guideLine_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGuideLineAttribute((undefined as Array<GuideLineStyle> | undefined));
                }
            }
        }
        if (this._barrier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barrier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarrierAttribute((this._barrier_0_0value as Array<BarrierStyle> | undefined));
                    this._barrier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barrier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barrier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarrierAttribute((undefined as Array<BarrierStyle> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RelativeContainerModifier): void {
        super.mergeModifier(modifier)
        if (modifier._guideLine_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._guideLine_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.guideLine(modifier._guideLine_0_0value);
                    break;
                }
                default: {
                    this.guideLine((undefined as Array<GuideLineStyle> | undefined));
                }
            }
        }
        if (modifier._barrier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barrier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barrier(modifier._barrier_0_0value);
                    break;
                }
                default: {
                    this.barrier((undefined as Array<BarrierStyle> | undefined));
                }
            }
        }
    }
    guideLine(value: Array<GuideLineStyle> | undefined): this {
        if (((this._guideLine_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._guideLine_0_flag = AttributeUpdaterFlag.UPDATE
            this._guideLine_0_0value = value
        } else
        {
            this._guideLine_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barrier(value: Array<BarrierStyle> | undefined): this {
        if (((this._barrier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barrier_0_flag = AttributeUpdaterFlag.UPDATE
            this._barrier_0_0value = value
        } else
        {
            this._barrier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class BarrierStyle_serializer {
    public static write(buffer: SerializerBase, value: BarrierStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(TypeChecker.BarrierDirection_ToNumeric(valueHolderForDirection))
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
        const directionTmpResult : BarrierDirection = TypeChecker.BarrierDirection_FromNumeric(valueDeserializer.readInt32())
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
export class GuideLinePosition_serializer {
    public static write(buffer: SerializerBase, value: GuideLinePosition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            if (valueHolderForStartTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForStartTmpValueForIdx0  = valueHolderForStartTmpValue as string
                valueSerializer.writeString(valueHolderForStartTmpValueForIdx0)
            } else if (valueHolderForStartTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForStartTmpValueForIdx1  = valueHolderForStartTmpValue as number
                valueSerializer.writeNumber(valueHolderForStartTmpValueForIdx1)
            } else if (valueHolderForStartTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForEndTmpValueForIdx0  = valueHolderForEndTmpValue as string
                valueSerializer.writeString(valueHolderForEndTmpValueForIdx0)
            } else if (valueHolderForEndTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForEndTmpValueForIdx1  = valueHolderForEndTmpValue as number
                valueSerializer.writeNumber(valueHolderForEndTmpValueForIdx1)
            } else if (valueHolderForEndTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
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
        let startTmpBuf : Dimension | undefined
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
        let endTmpBuf : Dimension | undefined
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
        valueSerializer.writeInt32(TypeChecker.Axis_ToNumeric(valueHolderForDirection))
        const valueHolderForPosition  = value.position
        GuideLinePosition_serializer.write(valueSerializer, valueHolderForPosition)
    }
    public static read(buffer: DeserializerBase): GuideLineStyle {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const directionTmpResult : Axis = TypeChecker.Axis_FromNumeric(valueDeserializer.readInt32())
        const positionTmpResult : GuideLinePosition = GuideLinePosition_serializer.read(valueDeserializer)
        let value : GuideLineStyle = ({id: idTmpResult, direction: directionTmpResult, position: positionTmpResult} as GuideLineStyle)
        return value
    }
}

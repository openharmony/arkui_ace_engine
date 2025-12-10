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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookRelativeContainerAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Dimension } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { Axis } from './enums'
import { RelativeContainerModifier } from './../RelativeContainerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkRelativeContainerPeer extends ArkCommonMethodPeer {
    attributeSet?: RelativeContainerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
            if (valueTmpValue instanceof Array) {
                if (valueTmpValue.length == 0) {
                    thisSerializer.writeInt8((0).toByte())
                    thisSerializer.writeInt32(0)
                } else {
                    const valueTmpValueElem  = valueTmpValue[0]
                    if (valueTmpValueElem instanceof BarrierStyle) {
                        thisSerializer.writeInt8((0).toByte())
                        const valueTmpValueForIdx0  = valueTmpValue as Array<BarrierStyle>
                        thisSerializer.writeInt32((valueTmpValueForIdx0.length).toInt())
                        for (let valueTmpValueForIdx0CounterI = 0; valueTmpValueForIdx0CounterI < valueTmpValueForIdx0.length; valueTmpValueForIdx0CounterI++) {
                            const valueTmpValueForIdx0TmpElement : BarrierStyle = valueTmpValueForIdx0[valueTmpValueForIdx0CounterI]
                            BarrierStyle_serializer.write(thisSerializer, valueTmpValueForIdx0TmpElement)
                        }
                    } else if (valueTmpValueElem instanceof LocalizedBarrierStyle) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1  = valueTmpValue as Array<LocalizedBarrierStyle>
                        thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                        for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                            const valueTmpValueForIdx1TmpElement : LocalizedBarrierStyle = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                            LocalizedBarrierStyle_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement)
                        }
                    }
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
        throw new Error('Unimplemented method setRelativeContainerOptions')
    }
    guideLine(value: Array<GuideLineStyle> | undefined): this {
        throw new Error('Unimplemented method guideLine')
    }
    barrier(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): this {
        throw new Error('Unimplemented method barrier')
    }
    attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkRelativeContainerComponent extends ArkCommonMethodComponent implements RelativeContainerAttribute {
    getPeer(): ArkRelativeContainerPeer {
        return (this.peer as ArkRelativeContainerPeer)
    }
    public setRelativeContainerOptions(): this {
        if (this.checkPriority('setRelativeContainerOptions')) {
            this.getPeer()?.setRelativeContainerOptionsAttribute()
            this.applyOptionsFinish('RelativeContainerAttribute');
            return this
        }
        return this
    }
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        if (this.checkPriority('guideLine')) {
            const value_casted = value as (Array<GuideLineStyle> | undefined)
            this.getPeer()?.setGuideLineAttribute(value_casted)
            return this
        }
        return this
    }
    public barrier(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): this {
        if (this.checkPriority('barrier')) {
            const value_casted = value as (Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined)
            this.getPeer()?.setBarrierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRelativeContainerAttributeModifier(this, value);
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
export function RelativeContainerImpl(
    @memo @memo_skip
    style: ((attributes: RelativeContainerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRelativeContainerComponent>((): ArkRelativeContainerComponent => {
        return new ArkRelativeContainerComponent()
    })
    NodeAttach<ArkRelativeContainerPeer>((): ArkRelativeContainerPeer => ArkRelativeContainerPeer.create(receiver), (_: ArkRelativeContainerPeer): void => {
        style?.(receiver)
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
            } else if (valueHolderForStartTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStartTmpValueForIdx2  = valueHolderForStartTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStartTmpValueForIdx2)
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
            } else if (valueHolderForEndTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForEndTmpValueForIdx2  = valueHolderForEndTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForEndTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GuideLinePosition {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : Dimension | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let startTmpBufOpt : string | number | global_resource_Resource | undefined
            if (startTmpBufOptUnionSelector == (0).toByte()) {
                startTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (startTmpBufOptUnionSelector == (1).toByte()) {
                startTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (startTmpBufOptUnionSelector == (2).toByte()) {
                startTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for startTmpBufOpt has to be chosen through deserialisation.')
            }
            startTmpBuf = (startTmpBufOpt as string | number | global_resource_Resource)
        }
        const startTmpResult : Dimension | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : Dimension | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let endTmpBufOpt : string | number | global_resource_Resource | undefined
            if (endTmpBufOptUnionSelector == (0).toByte()) {
                endTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (endTmpBufOptUnionSelector == (1).toByte()) {
                endTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (endTmpBufOptUnionSelector == (2).toByte()) {
                endTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for endTmpBufOpt has to be chosen through deserialisation.')
            }
            endTmpBuf = (endTmpBufOpt as string | number | global_resource_Resource)
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

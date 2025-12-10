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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { HorizontalAlign, FlexAlign } from './enums'
import { AttributeModifier, hookColumnAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Resource as global_resource_Resource } from 'global.resource'
import { ColumnModifier } from './../ColumnModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkColumnPeer extends ArkCommonMethodPeer {
    attributeSet?: ColumnModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkColumnPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Column_construct(peerId, flags)
        const _peer  = new ArkColumnPeer(_peerPtr, peerId, 'Column', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setColumnOptionsAttribute(options?: ColumnOptions | ColumnOptionsV2): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            if (optionsTmpValue instanceof ColumnOptions) {
                thisSerializer.writeInt8((0).toByte())
                const optionsTmpValueForIdx0  = optionsTmpValue as ColumnOptions
                ColumnOptions_serializer.write(thisSerializer, optionsTmpValueForIdx0)
            } else if (optionsTmpValue instanceof ColumnOptionsV2) {
                thisSerializer.writeInt8((1).toByte())
                const optionsTmpValueForIdx1  = optionsTmpValue as ColumnOptionsV2
                ColumnOptionsV2_serializer.write(thisSerializer, optionsTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnInterface_setColumnOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: HorizontalAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as HorizontalAlign)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJustifyContentAttribute(value: FlexAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FlexAlign)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setJustifyContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PointLightStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setReverseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setReverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SpaceType = string | double | global_resource_Resource;
export interface ColumnOptions {
    space?: string | double;
}
export interface ColumnOptionsV2 {
    space?: SpaceType;
}
export interface ColumnAttribute extends CommonMethod {
    setColumnOptions(options?: ColumnOptions | ColumnOptionsV2): this {
        throw new Error('Unimplemented method setColumnOptions')
    }
    alignItems(value: HorizontalAlign | undefined): this {
        throw new Error('Unimplemented method alignItems')
    }
    justifyContent(value: FlexAlign | undefined): this {
        throw new Error('Unimplemented method justifyContent')
    }
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error('Unimplemented method pointLight')
    }
    reverse(value: boolean | undefined): this {
        throw new Error('Unimplemented method reverse')
    }
    attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkColumnComponent extends ArkCommonMethodComponent implements ColumnAttribute {
    getPeer(): ArkColumnPeer {
        return (this.peer as ArkColumnPeer)
    }
    public setColumnOptions(options?: ColumnOptions | ColumnOptionsV2): this {
        if (this.checkPriority('setColumnOptions')) {
            const options_casted = options as (ColumnOptions | ColumnOptionsV2 | undefined)
            this.getPeer()?.setColumnOptionsAttribute(options_casted)
            this.applyOptionsFinish('ColumnAttribute');
            return this
        }
        return this
    }
    public alignItems(value: HorizontalAlign | undefined): this {
        if (this.checkPriority('alignItems')) {
            const value_casted = value as (HorizontalAlign | undefined)
            this.getPeer()?.setAlignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        if (this.checkPriority('justifyContent')) {
            const value_casted = value as (FlexAlign | undefined)
            this.getPeer()?.setJustifyContentAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority('pointLight')) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority('reverse')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setReverseAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookColumnAttributeModifier(this, value);
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
export function ColumnImpl(
    @memo @memo_skip
    style: ((attributes: ColumnAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkColumnComponent>((): ArkColumnComponent => {
        return new ArkColumnComponent()
    })
    NodeAttach<ArkColumnPeer>((): ArkColumnPeer => ArkColumnPeer.create(receiver), (_: ArkColumnPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ColumnOptions_serializer {
    public static write(buffer: SerializerBase, value: ColumnOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSpaceTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ColumnOptions {
        let valueDeserializer : DeserializerBase = buffer
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let spaceTmpBuf : string | double | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBufOpt : string | double | undefined
            if (spaceTmpBufOptUnionSelector == (0).toByte()) {
                spaceTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (spaceTmpBufOptUnionSelector == (1).toByte()) {
                spaceTmpBufOpt = valueDeserializer.readFloat64()
            } else {
                throw new Error('One of the branches for spaceTmpBufOpt has to be chosen through deserialisation.')
            }
            spaceTmpBuf = (spaceTmpBufOpt as string | double)
        }
        const spaceTmpResult : string | double | undefined = spaceTmpBuf
        let value : ColumnOptions = ({space: spaceTmpResult} as ColumnOptions)
        return value
    }
}
export class ColumnOptionsV2_serializer {
    public static write(buffer: SerializerBase, value: ColumnOptionsV2): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSpaceTmpValueForIdx1)
            } else if (valueHolderForSpaceTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSpaceTmpValueForIdx2  = valueHolderForSpaceTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSpaceTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ColumnOptionsV2 {
        let valueDeserializer : DeserializerBase = buffer
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let spaceTmpBuf : SpaceType | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBufOpt : string | double | global_resource_Resource | undefined
            if (spaceTmpBufOptUnionSelector == (0).toByte()) {
                spaceTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (spaceTmpBufOptUnionSelector == (1).toByte()) {
                spaceTmpBufOpt = valueDeserializer.readFloat64()
            } else if (spaceTmpBufOptUnionSelector == (2).toByte()) {
                spaceTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for spaceTmpBufOpt has to be chosen through deserialisation.')
            }
            spaceTmpBuf = (spaceTmpBufOpt as string | double | global_resource_Resource)
        }
        const spaceTmpResult : SpaceType | undefined = spaceTmpBuf
        let value : ColumnOptionsV2 = ({space: spaceTmpResult} as ColumnOptionsV2)
        return value
    }
}

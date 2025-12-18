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
import { AttributeModifier, hookColumnSplitAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Dimension } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { ColumnSplitModifier } from './../ColumnSplitModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkColumnSplitPeer extends ArkCommonMethodPeer {
    attributeSet?: ColumnSplitModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkColumnSplitPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ColumnSplit_construct(peerId, flags)
        const _peer  = new ArkColumnSplitPeer(_peerPtr, peerId, 'ColumnSplit', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setColumnSplitOptionsAttribute(): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        ArkUIGeneratedNativeModule._ColumnSplitInterface_setColumnSplitOptions(this.peer.ptr)
    }
    setResizeableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnSplitAttribute_setResizeable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ColumnSplitDividerStyle | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ColumnSplitDividerStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnSplitAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ColumnSplitDividerStyle {
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export interface ColumnSplitAttribute extends CommonMethod {
    setColumnSplitOptions(): this {
        throw new Error('Unimplemented method setColumnSplitOptions')
    }
    resizeable(value: boolean | undefined): this {
        throw new Error('Unimplemented method resizeable')
    }
    divider(value: ColumnSplitDividerStyle | null | undefined): this {
        throw new Error('Unimplemented method divider')
    }
    attributeModifier(value: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkColumnSplitComponent extends ArkCommonMethodComponent implements ColumnSplitAttribute {
    getPeer(): ArkColumnSplitPeer {
        return (this.peer as ArkColumnSplitPeer)
    }
    public setColumnSplitOptions(): this {
        if (this.checkPriority('setColumnSplitOptions')) {
            this.getPeer()?.setColumnSplitOptionsAttribute()
            this.applyOptionsFinish('ColumnSplitAttribute');
            return this
        }
        return this
    }
    public resizeable(value: boolean | undefined): this {
        if (this.checkPriority('resizeable')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setResizeableAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: ColumnSplitDividerStyle | null | undefined): this {
        if (this.checkPriority('divider')) {
            const value_casted = value as (ColumnSplitDividerStyle | null | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookColumnSplitAttributeModifier(this, value);
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
export function ColumnSplitImpl(
    @memo @memo_skip
    style: ((attributes: ColumnSplitAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkColumnSplitComponent>((): ArkColumnSplitComponent => {
        return new ArkColumnSplitComponent()
    })
    NodeAttach<ArkColumnSplitPeer>((): ArkColumnSplitPeer => ArkColumnSplitPeer.create(receiver), (_: ArkColumnSplitPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ColumnSplitDividerStyle_serializer {
    public static write(buffer: SerializerBase, value: ColumnSplitDividerStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStartMargin  = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue  = valueHolderForStartMargin!
            if (valueHolderForStartMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartMarginTmpValueForIdx0  = valueHolderForStartMarginTmpValue as string
                valueSerializer.writeString(valueHolderForStartMarginTmpValueForIdx0)
            } else if (valueHolderForStartMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStartMarginTmpValueForIdx1  = valueHolderForStartMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForStartMarginTmpValueForIdx1)
            } else if (valueHolderForStartMarginTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStartMarginTmpValueForIdx2  = valueHolderForStartMarginTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStartMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin  = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue  = valueHolderForEndMargin!
            if (valueHolderForEndMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndMarginTmpValueForIdx0  = valueHolderForEndMarginTmpValue as string
                valueSerializer.writeString(valueHolderForEndMarginTmpValueForIdx0)
            } else if (valueHolderForEndMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForEndMarginTmpValueForIdx1  = valueHolderForEndMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForEndMarginTmpValueForIdx1)
            } else if (valueHolderForEndMarginTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForEndMarginTmpValueForIdx2  = valueHolderForEndMarginTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForEndMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ColumnSplitDividerStyle {
        let valueDeserializer : DeserializerBase = buffer
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startMarginTmpBuf : Dimension | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startMarginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let startMarginTmpBufOpt : string | number | global_resource_Resource | undefined
            if (startMarginTmpBufOptUnionSelector == (0).toByte()) {
                startMarginTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (startMarginTmpBufOptUnionSelector == (1).toByte()) {
                startMarginTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (startMarginTmpBufOptUnionSelector == (2).toByte()) {
                startMarginTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for startMarginTmpBufOpt has to be chosen through deserialisation.')
            }
            startMarginTmpBuf = (startMarginTmpBufOpt as string | number | global_resource_Resource)
        }
        const startMarginTmpResult : Dimension | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endMarginTmpBuf : Dimension | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endMarginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let endMarginTmpBufOpt : string | number | global_resource_Resource | undefined
            if (endMarginTmpBufOptUnionSelector == (0).toByte()) {
                endMarginTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (endMarginTmpBufOptUnionSelector == (1).toByte()) {
                endMarginTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (endMarginTmpBufOptUnionSelector == (2).toByte()) {
                endMarginTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for endMarginTmpBufOpt has to be chosen through deserialisation.')
            }
            endMarginTmpBuf = (endMarginTmpBufOpt as string | number | global_resource_Resource)
        }
        const endMarginTmpResult : Dimension | undefined = endMarginTmpBuf
        let value : ColumnSplitDividerStyle = ({startMargin: startMarginTmpResult, endMargin: endMarginTmpResult} as ColumnSplitDividerStyle)
        return value
    }
}

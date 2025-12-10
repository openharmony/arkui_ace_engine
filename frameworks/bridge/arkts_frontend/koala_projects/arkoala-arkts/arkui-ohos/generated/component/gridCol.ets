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
import { AttributeModifier, hookGridColAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { GridColModifier } from './../GridColModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkGridColPeer extends ArkCommonMethodPeer {
    attributeSet?: GridColModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridColPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridCol_construct(peerId, flags)
        const _peer  = new ArkGridColPeer(_peerPtr, peerId, 'GridCol', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridColOptionsAttribute(option?: GridColOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (option !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionTmpValue  = option!
            GridColOptions_serializer.write(thisSerializer, optionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridColInterface_setGridColOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSpanAttribute(value: int32 | GridColColumnOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof GridColColumnOption) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as GridColColumnOption
                GridColColumnOption_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridColAttribute_setSpan(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGridColOffsetAttribute(value: int32 | GridColColumnOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof GridColColumnOption) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as GridColColumnOption
                GridColColumnOption_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridColAttribute_setGridColOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOrderAttribute(value: int32 | GridColColumnOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof GridColColumnOption) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as GridColColumnOption
                GridColColumnOption_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridColAttribute_setOrder(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GridColColumnOption {
    xs?: int32;
    sm?: int32;
    md?: int32;
    lg?: int32;
    xl?: int32;
    xxl?: int32;
}
export interface GridColOptions {
    span?: int32 | GridColColumnOption;
    offset?: int32 | GridColColumnOption;
    order?: int32 | GridColColumnOption;
}
export interface GridColAttribute extends CommonMethod {
    setGridColOptions(option?: GridColOptions): this {
        throw new Error('Unimplemented method setGridColOptions')
    }
    span(value: int32 | GridColColumnOption | undefined): this {
        throw new Error('Unimplemented method span')
    }
    gridColOffset(value: int32 | GridColColumnOption | undefined): this {
        throw new Error('Unimplemented method gridColOffset')
    }
    order(value: int32 | GridColColumnOption | undefined): this {
        throw new Error('Unimplemented method order')
    }
    attributeModifier(value: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkGridColComponent extends ArkCommonMethodComponent implements GridColAttribute {
    getPeer(): ArkGridColPeer {
        return (this.peer as ArkGridColPeer)
    }
    public setGridColOptions(option?: GridColOptions): this {
        if (this.checkPriority('setGridColOptions')) {
            const option_casted = option as (GridColOptions | undefined)
            this.getPeer()?.setGridColOptionsAttribute(option_casted)
            this.applyOptionsFinish('GridColAttribute');
            return this
        }
        return this
    }
    public span(value: int32 | GridColColumnOption | undefined): this {
        if (this.checkPriority('span')) {
            const value_casted = value as (int32 | GridColColumnOption | undefined)
            this.getPeer()?.setSpanAttribute(value_casted)
            return this
        }
        return this
    }
    public gridColOffset(value: int32 | GridColColumnOption | undefined): this {
        if (this.checkPriority('gridColOffset')) {
            const value_casted = value as (int32 | GridColColumnOption | undefined)
            this.getPeer()?.setGridColOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public order(value: int32 | GridColColumnOption | undefined): this {
        if (this.checkPriority('order')) {
            const value_casted = value as (int32 | GridColColumnOption | undefined)
            this.getPeer()?.setOrderAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookGridColAttributeModifier(this, value);
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
export function GridColImpl(
    @memo @memo_skip
    style: ((attributes: GridColAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkGridColComponent>((): ArkGridColComponent => {
        return new ArkGridColComponent()
    })
    NodeAttach<ArkGridColPeer>((): ArkGridColPeer => ArkGridColPeer.create(receiver), (_: ArkGridColPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class GridColColumnOption_serializer {
    public static write(buffer: SerializerBase, value: GridColColumnOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXs  = value.xs
        if (valueHolderForXs !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXsTmpValue  = valueHolderForXs!
            valueSerializer.writeInt32(valueHolderForXsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSm  = value.sm
        if (valueHolderForSm !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSmTmpValue  = valueHolderForSm!
            valueSerializer.writeInt32(valueHolderForSmTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMd  = value.md
        if (valueHolderForMd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMdTmpValue  = valueHolderForMd!
            valueSerializer.writeInt32(valueHolderForMdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLg  = value.lg
        if (valueHolderForLg !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLgTmpValue  = valueHolderForLg!
            valueSerializer.writeInt32(valueHolderForLgTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXl  = value.xl
        if (valueHolderForXl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXlTmpValue  = valueHolderForXl!
            valueSerializer.writeInt32(valueHolderForXlTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXxl  = value.xxl
        if (valueHolderForXxl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXxlTmpValue  = valueHolderForXxl!
            valueSerializer.writeInt32(valueHolderForXxlTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridColColumnOption {
        let valueDeserializer : DeserializerBase = buffer
        const xsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xsTmpBuf : int32 | undefined = undefined
        if ((xsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xsTmpBuf = valueDeserializer.readInt32()
        }
        const xsTmpResult : int32 | undefined = xsTmpBuf
        const smTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let smTmpBuf : int32 | undefined = undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            smTmpBuf = valueDeserializer.readInt32()
        }
        const smTmpResult : int32 | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let mdTmpBuf : int32 | undefined = undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mdTmpBuf = valueDeserializer.readInt32()
        }
        const mdTmpResult : int32 | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lgTmpBuf : int32 | undefined = undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lgTmpBuf = valueDeserializer.readInt32()
        }
        const lgTmpResult : int32 | undefined = lgTmpBuf
        const xlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xlTmpBuf : int32 | undefined = undefined
        if ((xlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xlTmpBuf = valueDeserializer.readInt32()
        }
        const xlTmpResult : int32 | undefined = xlTmpBuf
        const xxlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xxlTmpBuf : int32 | undefined = undefined
        if ((xxlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xxlTmpBuf = valueDeserializer.readInt32()
        }
        const xxlTmpResult : int32 | undefined = xxlTmpBuf
        let value : GridColColumnOption = ({xs: xsTmpResult, sm: smTmpResult, md: mdTmpResult, lg: lgTmpResult, xl: xlTmpResult, xxl: xxlTmpResult} as GridColColumnOption)
        return value
    }
}
export class GridColOptions_serializer {
    public static write(buffer: SerializerBase, value: GridColOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpan  = value.span
        if (valueHolderForSpan !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpanTmpValue  = valueHolderForSpan!
            if (valueHolderForSpanTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSpanTmpValueForIdx0  = valueHolderForSpanTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSpanTmpValueForIdx0)
            } else if (valueHolderForSpanTmpValue instanceof GridColColumnOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSpanTmpValueForIdx1  = valueHolderForSpanTmpValue as GridColColumnOption
                GridColColumnOption_serializer.write(valueSerializer, valueHolderForSpanTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            if (valueHolderForOffsetTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOffsetTmpValueForIdx0  = valueHolderForOffsetTmpValue as int32
                valueSerializer.writeInt32(valueHolderForOffsetTmpValueForIdx0)
            } else if (valueHolderForOffsetTmpValue instanceof GridColColumnOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetTmpValueForIdx1  = valueHolderForOffsetTmpValue as GridColColumnOption
                GridColColumnOption_serializer.write(valueSerializer, valueHolderForOffsetTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOrder  = value.order
        if (valueHolderForOrder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOrderTmpValue  = valueHolderForOrder!
            if (valueHolderForOrderTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOrderTmpValueForIdx0  = valueHolderForOrderTmpValue as int32
                valueSerializer.writeInt32(valueHolderForOrderTmpValueForIdx0)
            } else if (valueHolderForOrderTmpValue instanceof GridColColumnOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOrderTmpValueForIdx1  = valueHolderForOrderTmpValue as GridColColumnOption
                GridColColumnOption_serializer.write(valueSerializer, valueHolderForOrderTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridColOptions {
        let valueDeserializer : DeserializerBase = buffer
        const spanTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let spanTmpBuf : int32 | GridColColumnOption | undefined = undefined
        if ((spanTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spanTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let spanTmpBufOpt : int32 | GridColColumnOption | undefined
            if (spanTmpBufOptUnionSelector == (0).toByte()) {
                spanTmpBufOpt = valueDeserializer.readInt32()
            } else if (spanTmpBufOptUnionSelector == (1).toByte()) {
                spanTmpBufOpt = GridColColumnOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for spanTmpBufOpt has to be chosen through deserialisation.')
            }
            spanTmpBuf = (spanTmpBufOpt as int32 | GridColColumnOption)
        }
        const spanTmpResult : int32 | GridColColumnOption | undefined = spanTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : int32 | GridColColumnOption | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let offsetTmpBufOpt : int32 | GridColColumnOption | undefined
            if (offsetTmpBufOptUnionSelector == (0).toByte()) {
                offsetTmpBufOpt = valueDeserializer.readInt32()
            } else if (offsetTmpBufOptUnionSelector == (1).toByte()) {
                offsetTmpBufOpt = GridColColumnOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for offsetTmpBufOpt has to be chosen through deserialisation.')
            }
            offsetTmpBuf = (offsetTmpBufOpt as int32 | GridColColumnOption)
        }
        const offsetTmpResult : int32 | GridColColumnOption | undefined = offsetTmpBuf
        const orderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let orderTmpBuf : int32 | GridColColumnOption | undefined = undefined
        if ((orderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const orderTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let orderTmpBufOpt : int32 | GridColColumnOption | undefined
            if (orderTmpBufOptUnionSelector == (0).toByte()) {
                orderTmpBufOpt = valueDeserializer.readInt32()
            } else if (orderTmpBufOptUnionSelector == (1).toByte()) {
                orderTmpBufOpt = GridColColumnOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for orderTmpBufOpt has to be chosen through deserialisation.')
            }
            orderTmpBuf = (orderTmpBufOpt as int32 | GridColColumnOption)
        }
        const orderTmpResult : int32 | GridColColumnOption | undefined = orderTmpBuf
        let value : GridColOptions = ({span: spanTmpResult, offset: offsetTmpResult, order: orderTmpResult} as GridColOptions)
        return value
    }
}

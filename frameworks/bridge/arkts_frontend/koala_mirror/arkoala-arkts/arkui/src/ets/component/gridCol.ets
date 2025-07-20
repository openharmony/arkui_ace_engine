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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridColPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridColPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridCol_construct(peerId, flags)
        const _peer  = new ArkGridColPeer(_peerPtr, peerId, "GridCol", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridColOptionsAttribute(option?: GridColOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let option_type : int32 = RuntimeType.UNDEFINED
        option_type = runtimeType(option)
        thisSerializer.writeInt8((option_type).toChar())
        if ((option_type) != (RuntimeType.UNDEFINED)) {
            const option_value  = option!
            GridColOptions_serializer.write(thisSerializer, option_value)
        }
        ArkUIGeneratedNativeModule._GridColInterface_setGridColOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSpanAttribute(value: number | GridColColumnOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as GridColColumnOption
                GridColColumnOption_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridColAttribute_setSpan(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGridColOffsetAttribute(value: number | GridColColumnOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as GridColColumnOption
                GridColColumnOption_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridColAttribute_setGridColOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOrderAttribute(value: number | GridColColumnOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as GridColColumnOption
                GridColColumnOption_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridColAttribute_setOrder(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GridColColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
export interface GridColOptions {
    span?: number | GridColColumnOption;
    offset?: number | GridColColumnOption;
    order?: number | GridColColumnOption;
}
export interface GridColAttribute extends CommonMethod {
    span(value: number | GridColColumnOption | undefined): this {
        throw new Error("Unimplemented method span")
    }
    gridColOffset(value: number | GridColColumnOption | undefined): this {
        throw new Error("Unimplemented method gridColOffset")
    }
    order(value: number | GridColColumnOption | undefined): this {
        throw new Error("Unimplemented method order")
    }
    attributeModifier(value: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkGridColStyle extends ArkCommonMethodStyle implements GridColAttribute {
    span_value?: number | GridColColumnOption | undefined
    gridColOffset_value?: number | GridColColumnOption | undefined
    order_value?: number | GridColColumnOption | undefined
    attributeModifier_value?: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined
    public span(value: number | GridColColumnOption | undefined): this {
        return this
    }
    public gridColOffset(value: number | GridColColumnOption | undefined): this {
        return this
    }
    public order(value: number | GridColColumnOption | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: GridColAttribute): void {
        super.apply(target)
        if (this.span_value !== undefined)
            target.span(this.span_value!)
        if (this.gridColOffset_value !== undefined)
            target.gridColOffset(this.gridColOffset_value!)
        if (this.order_value !== undefined)
            target.order(this.order_value!)
    }
}

export class ArkGridColComponent extends ArkCommonMethodComponent implements GridColAttribute {
    getPeer(): ArkGridColPeer {
        return (this.peer as ArkGridColPeer)
    }
    public setGridColOptions(option?: GridColOptions): this {
        if (this.checkPriority("setGridColOptions")) {
            const option_casted = option as (GridColOptions | undefined)
            this.getPeer()?.setGridColOptionsAttribute(option_casted)
            return this
        }
        return this
    }
    public span(value: number | GridColColumnOption | undefined): this {
        if (this.checkPriority("span")) {
            const value_casted = value as (number | GridColColumnOption | undefined)
            this.getPeer()?.setSpanAttribute(value_casted)
            return this
        }
        return this
    }
    public gridColOffset(value: number | GridColColumnOption | undefined): this {
        if (this.checkPriority("gridColOffset")) {
            const value_casted = value as (number | GridColColumnOption | undefined)
            this.getPeer()?.setGridColOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public order(value: number | GridColColumnOption | undefined): this {
        if (this.checkPriority("order")) {
            const value_casted = value as (number | GridColColumnOption | undefined)
            this.getPeer()?.setOrderAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withGridColStyle(receiver: GridColAttribute, modifier: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkGridColStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("GridCol")
// export function GridCol(
//     option?: GridColOptions,
//     @memo
//     content_?: () => void,
// ): GridColAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function GridCol(
    @memo
    style: ((attributes: GridColAttribute) => void) | undefined,
    option?: GridColOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridColComponent>((): ArkGridColComponent => {
        return new ArkGridColComponent()
    })
    NodeAttach<ArkGridColPeer>((): ArkGridColPeer => ArkGridColPeer.create(receiver), (_: ArkGridColPeer): void => {
        receiver.setGridColOptions(option)
        style?.(receiver)
        withGridColStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkGridColSet extends ArkCommonMethodSet implements GridColAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _span_flag?: boolean
    _span0_value?: number | GridColColumnOption | undefined
    _gridColOffset_flag?: boolean
    _gridColOffset0_value?: number | GridColColumnOption | undefined
    _order_flag?: boolean
    _order0_value?: number | GridColColumnOption | undefined
    applyModifierPatch(component: GridColAttribute): void {
        if (this._span_flag)
            component.span((this._span0_value as number | GridColColumnOption | undefined))
        if (this._gridColOffset_flag)
            component.gridColOffset((this._gridColOffset0_value as number | GridColColumnOption | undefined))
        if (this._order_flag)
            component.order((this._order0_value as number | GridColColumnOption | undefined))
    }
    public span(value: number | GridColColumnOption | undefined): this {
        this._span_flag = true
        this._span0_value = value
        return this
    }
    public gridColOffset(value: number | GridColColumnOption | undefined): this {
        this._gridColOffset_flag = true
        this._gridColOffset0_value = value
        return this
    }
    public order(value: number | GridColColumnOption | undefined): this {
        this._order_flag = true
        this._order0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class GridColColumnOption_serializer {
    public static write(buffer: SerializerBase, value: GridColColumnOption): void {
        let valueSerializer : SerializerBase = buffer
        const value_xs  = value.xs
        let value_xs_type : int32 = RuntimeType.UNDEFINED
        value_xs_type = runtimeType(value_xs)
        valueSerializer.writeInt8((value_xs_type).toChar())
        if ((value_xs_type) != (RuntimeType.UNDEFINED)) {
            const value_xs_value  = value_xs!
            valueSerializer.writeNumber(value_xs_value)
        }
        const value_sm  = value.sm
        let value_sm_type : int32 = RuntimeType.UNDEFINED
        value_sm_type = runtimeType(value_sm)
        valueSerializer.writeInt8((value_sm_type).toChar())
        if ((value_sm_type) != (RuntimeType.UNDEFINED)) {
            const value_sm_value  = value_sm!
            valueSerializer.writeNumber(value_sm_value)
        }
        const value_md  = value.md
        let value_md_type : int32 = RuntimeType.UNDEFINED
        value_md_type = runtimeType(value_md)
        valueSerializer.writeInt8((value_md_type).toChar())
        if ((value_md_type) != (RuntimeType.UNDEFINED)) {
            const value_md_value  = value_md!
            valueSerializer.writeNumber(value_md_value)
        }
        const value_lg  = value.lg
        let value_lg_type : int32 = RuntimeType.UNDEFINED
        value_lg_type = runtimeType(value_lg)
        valueSerializer.writeInt8((value_lg_type).toChar())
        if ((value_lg_type) != (RuntimeType.UNDEFINED)) {
            const value_lg_value  = value_lg!
            valueSerializer.writeNumber(value_lg_value)
        }
        const value_xl  = value.xl
        let value_xl_type : int32 = RuntimeType.UNDEFINED
        value_xl_type = runtimeType(value_xl)
        valueSerializer.writeInt8((value_xl_type).toChar())
        if ((value_xl_type) != (RuntimeType.UNDEFINED)) {
            const value_xl_value  = value_xl!
            valueSerializer.writeNumber(value_xl_value)
        }
        const value_xxl  = value.xxl
        let value_xxl_type : int32 = RuntimeType.UNDEFINED
        value_xxl_type = runtimeType(value_xxl)
        valueSerializer.writeInt8((value_xxl_type).toChar())
        if ((value_xxl_type) != (RuntimeType.UNDEFINED)) {
            const value_xxl_value  = value_xxl!
            valueSerializer.writeNumber(value_xxl_value)
        }
    }
    public static read(buffer: DeserializerBase): GridColColumnOption {
        let valueDeserializer : DeserializerBase = buffer
        const xs_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xs_buf : number | undefined
        if ((xs_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            xs_buf = (valueDeserializer.readNumber() as number)
        }
        const xs_result : number | undefined = xs_buf
        const sm_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sm_buf : number | undefined
        if ((sm_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            sm_buf = (valueDeserializer.readNumber() as number)
        }
        const sm_result : number | undefined = sm_buf
        const md_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let md_buf : number | undefined
        if ((md_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            md_buf = (valueDeserializer.readNumber() as number)
        }
        const md_result : number | undefined = md_buf
        const lg_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lg_buf : number | undefined
        if ((lg_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            lg_buf = (valueDeserializer.readNumber() as number)
        }
        const lg_result : number | undefined = lg_buf
        const xl_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xl_buf : number | undefined
        if ((xl_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            xl_buf = (valueDeserializer.readNumber() as number)
        }
        const xl_result : number | undefined = xl_buf
        const xxl_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xxl_buf : number | undefined
        if ((xxl_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            xxl_buf = (valueDeserializer.readNumber() as number)
        }
        const xxl_result : number | undefined = xxl_buf
        let value : GridColColumnOption = ({xs: xs_result, sm: sm_result, md: md_result, lg: lg_result, xl: xl_result, xxl: xxl_result} as GridColColumnOption)
        return value
    }
}
export class GridColOptions_serializer {
    public static write(buffer: SerializerBase, value: GridColOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_span  = value.span
        let value_span_type : int32 = RuntimeType.UNDEFINED
        value_span_type = runtimeType(value_span)
        valueSerializer.writeInt8((value_span_type).toChar())
        if ((value_span_type) != (RuntimeType.UNDEFINED)) {
            const value_span_value  = value_span!
            let value_span_value_type : int32 = RuntimeType.UNDEFINED
            value_span_value_type = runtimeType(value_span_value)
            if (RuntimeType.NUMBER == value_span_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_span_value_0  = value_span_value as number
                valueSerializer.writeNumber(value_span_value_0)
            }
            else if (RuntimeType.OBJECT == value_span_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_span_value_1  = value_span_value as GridColColumnOption
                GridColColumnOption_serializer.write(valueSerializer, value_span_value_1)
            }
        }
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8((value_offset_type).toChar())
        if ((value_offset_type) != (RuntimeType.UNDEFINED)) {
            const value_offset_value  = value_offset!
            let value_offset_value_type : int32 = RuntimeType.UNDEFINED
            value_offset_value_type = runtimeType(value_offset_value)
            if (RuntimeType.NUMBER == value_offset_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_offset_value_0  = value_offset_value as number
                valueSerializer.writeNumber(value_offset_value_0)
            }
            else if (RuntimeType.OBJECT == value_offset_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_offset_value_1  = value_offset_value as GridColColumnOption
                GridColColumnOption_serializer.write(valueSerializer, value_offset_value_1)
            }
        }
        const value_order  = value.order
        let value_order_type : int32 = RuntimeType.UNDEFINED
        value_order_type = runtimeType(value_order)
        valueSerializer.writeInt8((value_order_type).toChar())
        if ((value_order_type) != (RuntimeType.UNDEFINED)) {
            const value_order_value  = value_order!
            let value_order_value_type : int32 = RuntimeType.UNDEFINED
            value_order_value_type = runtimeType(value_order_value)
            if (RuntimeType.NUMBER == value_order_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_order_value_0  = value_order_value as number
                valueSerializer.writeNumber(value_order_value_0)
            }
            else if (RuntimeType.OBJECT == value_order_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_order_value_1  = value_order_value as GridColColumnOption
                GridColColumnOption_serializer.write(valueSerializer, value_order_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): GridColOptions {
        let valueDeserializer : DeserializerBase = buffer
        const span_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let span_buf : number | GridColColumnOption | undefined
        if ((span_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const span_buf__selector : int32 = valueDeserializer.readInt8()
            let span_buf_ : number | GridColColumnOption | undefined
            if (span_buf__selector == (0).toChar()) {
                span_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (span_buf__selector == (1).toChar()) {
                span_buf_ = GridColColumnOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for span_buf_ has to be chosen through deserialisation.")
            }
            span_buf = (span_buf_ as number | GridColColumnOption)
        }
        const span_result : number | GridColColumnOption | undefined = span_buf
        const offset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offset_buf : number | GridColColumnOption | undefined
        if ((offset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const offset_buf__selector : int32 = valueDeserializer.readInt8()
            let offset_buf_ : number | GridColColumnOption | undefined
            if (offset_buf__selector == (0).toChar()) {
                offset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offset_buf__selector == (1).toChar()) {
                offset_buf_ = GridColColumnOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offset_buf_ has to be chosen through deserialisation.")
            }
            offset_buf = (offset_buf_ as number | GridColColumnOption)
        }
        const offset_result : number | GridColColumnOption | undefined = offset_buf
        const order_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let order_buf : number | GridColColumnOption | undefined
        if ((order_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const order_buf__selector : int32 = valueDeserializer.readInt8()
            let order_buf_ : number | GridColColumnOption | undefined
            if (order_buf__selector == (0).toChar()) {
                order_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (order_buf__selector == (1).toChar()) {
                order_buf_ = GridColColumnOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for order_buf_ has to be chosen through deserialisation.")
            }
            order_buf = (order_buf_ as number | GridColColumnOption)
        }
        const order_result : number | GridColColumnOption | undefined = order_buf
        let value : GridColOptions = ({span: span_result, offset: offset_result, order: order_result} as GridColOptions)
        return value
    }
}

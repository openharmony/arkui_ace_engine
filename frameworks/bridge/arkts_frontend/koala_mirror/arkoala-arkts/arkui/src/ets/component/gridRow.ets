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
import { ItemAlign } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Length } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridRowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridRowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridRow_construct(peerId, flags)
        const _peer  = new ArkGridRowPeer(_peerPtr, peerId, "GridRow", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridRowOptionsAttribute(option?: GridRowOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let option_type : int32 = RuntimeType.UNDEFINED
        option_type = runtimeType(option)
        thisSerializer.writeInt8((option_type).toChar())
        if ((option_type) != (RuntimeType.UNDEFINED)) {
            const option_value  = option!
            GridRowOptions_serializer.write(thisSerializer, option_value)
        }
        ArkUIGeneratedNativeModule._GridRowInterface_setGridRowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBreakpointChangeAttribute(value: ((breakpoints: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridRowAttribute_setOnBreakpointChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: ItemAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ItemAlign)
            thisSerializer.writeInt32(TypeChecker.ItemAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridRowAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GridRowSizeOption {
    xs?: Length;
    sm?: Length;
    md?: Length;
    lg?: Length;
    xl?: Length;
    xxl?: Length;
}
export interface GridRowColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
export interface GutterOption {
    x?: Length | GridRowSizeOption;
    y?: Length | GridRowSizeOption;
}
export enum BreakpointsReference {
    WINDOW_SIZE = 0,
    WindowSize = 0,
    COMPONENT_SIZE = 1,
    ComponentSize = 1
}
export enum GridRowDirection {
    ROW = 0,
    Row = 0,
    ROW_REVERSE = 1,
    RowReverse = 1
}
export interface BreakPoints {
    value?: Array<string>;
    reference?: BreakpointsReference;
}
export interface GridRowOptions {
    gutter?: Length | GutterOption;
    columns?: number | GridRowColumnOption;
    breakpoints?: BreakPoints;
    direction?: GridRowDirection;
}
export interface GridRowAttribute extends CommonMethod {
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        throw new Error("Unimplemented method onBreakpointChange")
    }
    alignItems(value: ItemAlign | undefined): this {
        throw new Error("Unimplemented method alignItems")
    }
    attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkGridRowStyle extends ArkCommonMethodStyle implements GridRowAttribute {
    onBreakpointChange_value?: ((breakpoints: string) => void) | undefined
    alignItems_value?: ItemAlign | undefined
    attributeModifier_value?: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined
    public onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        return this
    }
    public alignItems(value: ItemAlign | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: GridRowAttribute): void {
        super.apply(target)
        if (this.onBreakpointChange_value !== undefined)
            target.onBreakpointChange(this.onBreakpointChange_value!)
        if (this.alignItems_value !== undefined)
            target.alignItems(this.alignItems_value!)
    }
}

export class ArkGridRowComponent extends ArkCommonMethodComponent implements GridRowAttribute {
    getPeer(): ArkGridRowPeer {
        return (this.peer as ArkGridRowPeer)
    }
    public setGridRowOptions(option?: GridRowOptions): this {
        if (this.checkPriority("setGridRowOptions")) {
            const option_casted = option as (GridRowOptions | undefined)
            this.getPeer()?.setGridRowOptionsAttribute(option_casted)
            return this
        }
        return this
    }
    public onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        if (this.checkPriority("onBreakpointChange")) {
            const value_casted = value as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.setOnBreakpointChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public alignItems(value: ItemAlign | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (ItemAlign | undefined)
            this.getPeer()?.setAlignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withGridRowStyle(receiver: GridRowAttribute, modifier: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkGridRowStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("GridRow")
// export function GridRow(
//     option?: GridRowOptions,
//     @memo
//     content_?: () => void,
// ): GridRowAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function GridRow(
    @memo
    style: ((attributes: GridRowAttribute) => void) | undefined,
    option?: GridRowOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridRowComponent>((): ArkGridRowComponent => {
        return new ArkGridRowComponent()
    })
    NodeAttach<ArkGridRowPeer>((): ArkGridRowPeer => ArkGridRowPeer.create(receiver), (_: ArkGridRowPeer): void => {
        receiver.setGridRowOptions(option)
        style?.(receiver)
        withGridRowStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkGridRowSet extends ArkCommonMethodSet implements GridRowAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onBreakpointChange_flag?: boolean
    _onBreakpointChange0_value?: ((breakpoints: string) => void) | undefined
    _alignItems_flag?: boolean
    _alignItems0_value?: ItemAlign | undefined
    applyModifierPatch(component: GridRowAttribute): void {
        if (this._onBreakpointChange_flag)
            component.onBreakpointChange((this._onBreakpointChange0_value as ((breakpoints: string) => void) | undefined))
        if (this._alignItems_flag)
            component.alignItems((this._alignItems0_value as ItemAlign | undefined))
    }
    public onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        this._onBreakpointChange_flag = true
        this._onBreakpointChange0_value = value
        return this
    }
    public alignItems(value: ItemAlign | undefined): this {
        this._alignItems_flag = true
        this._alignItems0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class BreakPoints_serializer {
    public static write(buffer: SerializerBase, value: BreakPoints): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        valueSerializer.writeInt8((value_value_type).toChar())
        if ((value_value_type) != (RuntimeType.UNDEFINED)) {
            const value_value_value  = value_value!
            valueSerializer.writeInt32((value_value_value.length).toInt())
            for (let value_value_value_counter_i = 0; value_value_value_counter_i < value_value_value.length; value_value_value_counter_i++) {
                const value_value_value_element : string = value_value_value[value_value_value_counter_i]
                valueSerializer.writeString(value_value_value_element)
            }
        }
        const value_reference  = value.reference
        let value_reference_type : int32 = RuntimeType.UNDEFINED
        value_reference_type = runtimeType(value_reference)
        valueSerializer.writeInt8((value_reference_type).toChar())
        if ((value_reference_type) != (RuntimeType.UNDEFINED)) {
            const value_reference_value  = (value_reference as BreakpointsReference)
            valueSerializer.writeInt32(TypeChecker.BreakpointsReference_ToNumeric(value_reference_value))
        }
    }
    public static read(buffer: DeserializerBase): BreakPoints {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let value_buf : Array<string> | undefined
        if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const value_buf__length : int32 = valueDeserializer.readInt32()
            let value_buf_ : Array<string> = new Array<string>(value_buf__length)
            for (let value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
                value_buf_[value_buf__i] = (valueDeserializer.readString() as string)
            }
            value_buf = value_buf_
        }
        const value_result : Array<string> | undefined = value_buf
        const reference_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let reference_buf : BreakpointsReference | undefined
        if ((reference_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            reference_buf = TypeChecker.BreakpointsReference_FromNumeric(valueDeserializer.readInt32())
        }
        const reference_result : BreakpointsReference | undefined = reference_buf
        let value : BreakPoints = ({value: value_result, reference: reference_result} as BreakPoints)
        return value
    }
}
export class GridRowColumnOption_serializer {
    public static write(buffer: SerializerBase, value: GridRowColumnOption): void {
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
    public static read(buffer: DeserializerBase): GridRowColumnOption {
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
        let value : GridRowColumnOption = ({xs: xs_result, sm: sm_result, md: md_result, lg: lg_result, xl: xl_result, xxl: xxl_result} as GridRowColumnOption)
        return value
    }
}
export class GridRowSizeOption_serializer {
    public static write(buffer: SerializerBase, value: GridRowSizeOption): void {
        let valueSerializer : SerializerBase = buffer
        const value_xs  = value.xs
        let value_xs_type : int32 = RuntimeType.UNDEFINED
        value_xs_type = runtimeType(value_xs)
        valueSerializer.writeInt8((value_xs_type).toChar())
        if ((value_xs_type) != (RuntimeType.UNDEFINED)) {
            const value_xs_value  = value_xs!
            let value_xs_value_type : int32 = RuntimeType.UNDEFINED
            value_xs_value_type = runtimeType(value_xs_value)
            if (RuntimeType.STRING == value_xs_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_xs_value_0  = value_xs_value as string
                valueSerializer.writeString(value_xs_value_0)
            }
            else if (RuntimeType.NUMBER == value_xs_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_xs_value_1  = value_xs_value as number
                valueSerializer.writeNumber(value_xs_value_1)
            }
            else if (RuntimeType.OBJECT == value_xs_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_xs_value_2  = value_xs_value as Resource
                Resource_serializer.write(valueSerializer, value_xs_value_2)
            }
        }
        const value_sm  = value.sm
        let value_sm_type : int32 = RuntimeType.UNDEFINED
        value_sm_type = runtimeType(value_sm)
        valueSerializer.writeInt8((value_sm_type).toChar())
        if ((value_sm_type) != (RuntimeType.UNDEFINED)) {
            const value_sm_value  = value_sm!
            let value_sm_value_type : int32 = RuntimeType.UNDEFINED
            value_sm_value_type = runtimeType(value_sm_value)
            if (RuntimeType.STRING == value_sm_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_sm_value_0  = value_sm_value as string
                valueSerializer.writeString(value_sm_value_0)
            }
            else if (RuntimeType.NUMBER == value_sm_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_sm_value_1  = value_sm_value as number
                valueSerializer.writeNumber(value_sm_value_1)
            }
            else if (RuntimeType.OBJECT == value_sm_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_sm_value_2  = value_sm_value as Resource
                Resource_serializer.write(valueSerializer, value_sm_value_2)
            }
        }
        const value_md  = value.md
        let value_md_type : int32 = RuntimeType.UNDEFINED
        value_md_type = runtimeType(value_md)
        valueSerializer.writeInt8((value_md_type).toChar())
        if ((value_md_type) != (RuntimeType.UNDEFINED)) {
            const value_md_value  = value_md!
            let value_md_value_type : int32 = RuntimeType.UNDEFINED
            value_md_value_type = runtimeType(value_md_value)
            if (RuntimeType.STRING == value_md_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_md_value_0  = value_md_value as string
                valueSerializer.writeString(value_md_value_0)
            }
            else if (RuntimeType.NUMBER == value_md_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_md_value_1  = value_md_value as number
                valueSerializer.writeNumber(value_md_value_1)
            }
            else if (RuntimeType.OBJECT == value_md_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_md_value_2  = value_md_value as Resource
                Resource_serializer.write(valueSerializer, value_md_value_2)
            }
        }
        const value_lg  = value.lg
        let value_lg_type : int32 = RuntimeType.UNDEFINED
        value_lg_type = runtimeType(value_lg)
        valueSerializer.writeInt8((value_lg_type).toChar())
        if ((value_lg_type) != (RuntimeType.UNDEFINED)) {
            const value_lg_value  = value_lg!
            let value_lg_value_type : int32 = RuntimeType.UNDEFINED
            value_lg_value_type = runtimeType(value_lg_value)
            if (RuntimeType.STRING == value_lg_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_lg_value_0  = value_lg_value as string
                valueSerializer.writeString(value_lg_value_0)
            }
            else if (RuntimeType.NUMBER == value_lg_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_lg_value_1  = value_lg_value as number
                valueSerializer.writeNumber(value_lg_value_1)
            }
            else if (RuntimeType.OBJECT == value_lg_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_lg_value_2  = value_lg_value as Resource
                Resource_serializer.write(valueSerializer, value_lg_value_2)
            }
        }
        const value_xl  = value.xl
        let value_xl_type : int32 = RuntimeType.UNDEFINED
        value_xl_type = runtimeType(value_xl)
        valueSerializer.writeInt8((value_xl_type).toChar())
        if ((value_xl_type) != (RuntimeType.UNDEFINED)) {
            const value_xl_value  = value_xl!
            let value_xl_value_type : int32 = RuntimeType.UNDEFINED
            value_xl_value_type = runtimeType(value_xl_value)
            if (RuntimeType.STRING == value_xl_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_xl_value_0  = value_xl_value as string
                valueSerializer.writeString(value_xl_value_0)
            }
            else if (RuntimeType.NUMBER == value_xl_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_xl_value_1  = value_xl_value as number
                valueSerializer.writeNumber(value_xl_value_1)
            }
            else if (RuntimeType.OBJECT == value_xl_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_xl_value_2  = value_xl_value as Resource
                Resource_serializer.write(valueSerializer, value_xl_value_2)
            }
        }
        const value_xxl  = value.xxl
        let value_xxl_type : int32 = RuntimeType.UNDEFINED
        value_xxl_type = runtimeType(value_xxl)
        valueSerializer.writeInt8((value_xxl_type).toChar())
        if ((value_xxl_type) != (RuntimeType.UNDEFINED)) {
            const value_xxl_value  = value_xxl!
            let value_xxl_value_type : int32 = RuntimeType.UNDEFINED
            value_xxl_value_type = runtimeType(value_xxl_value)
            if (RuntimeType.STRING == value_xxl_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_xxl_value_0  = value_xxl_value as string
                valueSerializer.writeString(value_xxl_value_0)
            }
            else if (RuntimeType.NUMBER == value_xxl_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_xxl_value_1  = value_xxl_value as number
                valueSerializer.writeNumber(value_xxl_value_1)
            }
            else if (RuntimeType.OBJECT == value_xxl_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_xxl_value_2  = value_xxl_value as Resource
                Resource_serializer.write(valueSerializer, value_xxl_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): GridRowSizeOption {
        let valueDeserializer : DeserializerBase = buffer
        const xs_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xs_buf : Length | undefined
        if ((xs_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const xs_buf__selector : int32 = valueDeserializer.readInt8()
            let xs_buf_ : string | number | Resource | undefined
            if (xs_buf__selector == (0).toChar()) {
                xs_buf_ = (valueDeserializer.readString() as string)
            }
            else if (xs_buf__selector == (1).toChar()) {
                xs_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (xs_buf__selector == (2).toChar()) {
                xs_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for xs_buf_ has to be chosen through deserialisation.")
            }
            xs_buf = (xs_buf_ as string | number | Resource)
        }
        const xs_result : Length | undefined = xs_buf
        const sm_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sm_buf : Length | undefined
        if ((sm_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const sm_buf__selector : int32 = valueDeserializer.readInt8()
            let sm_buf_ : string | number | Resource | undefined
            if (sm_buf__selector == (0).toChar()) {
                sm_buf_ = (valueDeserializer.readString() as string)
            }
            else if (sm_buf__selector == (1).toChar()) {
                sm_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (sm_buf__selector == (2).toChar()) {
                sm_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for sm_buf_ has to be chosen through deserialisation.")
            }
            sm_buf = (sm_buf_ as string | number | Resource)
        }
        const sm_result : Length | undefined = sm_buf
        const md_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let md_buf : Length | undefined
        if ((md_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const md_buf__selector : int32 = valueDeserializer.readInt8()
            let md_buf_ : string | number | Resource | undefined
            if (md_buf__selector == (0).toChar()) {
                md_buf_ = (valueDeserializer.readString() as string)
            }
            else if (md_buf__selector == (1).toChar()) {
                md_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (md_buf__selector == (2).toChar()) {
                md_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for md_buf_ has to be chosen through deserialisation.")
            }
            md_buf = (md_buf_ as string | number | Resource)
        }
        const md_result : Length | undefined = md_buf
        const lg_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lg_buf : Length | undefined
        if ((lg_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const lg_buf__selector : int32 = valueDeserializer.readInt8()
            let lg_buf_ : string | number | Resource | undefined
            if (lg_buf__selector == (0).toChar()) {
                lg_buf_ = (valueDeserializer.readString() as string)
            }
            else if (lg_buf__selector == (1).toChar()) {
                lg_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (lg_buf__selector == (2).toChar()) {
                lg_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for lg_buf_ has to be chosen through deserialisation.")
            }
            lg_buf = (lg_buf_ as string | number | Resource)
        }
        const lg_result : Length | undefined = lg_buf
        const xl_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xl_buf : Length | undefined
        if ((xl_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const xl_buf__selector : int32 = valueDeserializer.readInt8()
            let xl_buf_ : string | number | Resource | undefined
            if (xl_buf__selector == (0).toChar()) {
                xl_buf_ = (valueDeserializer.readString() as string)
            }
            else if (xl_buf__selector == (1).toChar()) {
                xl_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (xl_buf__selector == (2).toChar()) {
                xl_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for xl_buf_ has to be chosen through deserialisation.")
            }
            xl_buf = (xl_buf_ as string | number | Resource)
        }
        const xl_result : Length | undefined = xl_buf
        const xxl_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xxl_buf : Length | undefined
        if ((xxl_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const xxl_buf__selector : int32 = valueDeserializer.readInt8()
            let xxl_buf_ : string | number | Resource | undefined
            if (xxl_buf__selector == (0).toChar()) {
                xxl_buf_ = (valueDeserializer.readString() as string)
            }
            else if (xxl_buf__selector == (1).toChar()) {
                xxl_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (xxl_buf__selector == (2).toChar()) {
                xxl_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for xxl_buf_ has to be chosen through deserialisation.")
            }
            xxl_buf = (xxl_buf_ as string | number | Resource)
        }
        const xxl_result : Length | undefined = xxl_buf
        let value : GridRowSizeOption = ({xs: xs_result, sm: sm_result, md: md_result, lg: lg_result, xl: xl_result, xxl: xxl_result} as GridRowSizeOption)
        return value
    }
}
export class GutterOption_serializer {
    public static write(buffer: SerializerBase, value: GutterOption): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        let value_x_type : int32 = RuntimeType.UNDEFINED
        value_x_type = runtimeType(value_x)
        valueSerializer.writeInt8((value_x_type).toChar())
        if ((value_x_type) != (RuntimeType.UNDEFINED)) {
            const value_x_value  = value_x!
            let value_x_value_type : int32 = RuntimeType.UNDEFINED
            value_x_value_type = runtimeType(value_x_value)
            if ((RuntimeType.STRING == value_x_value_type) || (RuntimeType.NUMBER == value_x_value_type) || (RuntimeType.OBJECT == value_x_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_x_value_0  = value_x_value as Length
                let value_x_value_0_type : int32 = RuntimeType.UNDEFINED
                value_x_value_0_type = runtimeType(value_x_value_0)
                if (RuntimeType.STRING == value_x_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_x_value_0_0  = value_x_value_0 as string
                    valueSerializer.writeString(value_x_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_x_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_x_value_0_1  = value_x_value_0 as number
                    valueSerializer.writeNumber(value_x_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_x_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_x_value_0_2  = value_x_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_x_value_0_2)
                }
            }
            else if (TypeChecker.isGridRowSizeOption(value_x_value, false, false, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_x_value_1  = value_x_value as GridRowSizeOption
                GridRowSizeOption_serializer.write(valueSerializer, value_x_value_1)
            }
        }
        const value_y  = value.y
        let value_y_type : int32 = RuntimeType.UNDEFINED
        value_y_type = runtimeType(value_y)
        valueSerializer.writeInt8((value_y_type).toChar())
        if ((value_y_type) != (RuntimeType.UNDEFINED)) {
            const value_y_value  = value_y!
            let value_y_value_type : int32 = RuntimeType.UNDEFINED
            value_y_value_type = runtimeType(value_y_value)
            if ((RuntimeType.STRING == value_y_value_type) || (RuntimeType.NUMBER == value_y_value_type) || (RuntimeType.OBJECT == value_y_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_y_value_0  = value_y_value as Length
                let value_y_value_0_type : int32 = RuntimeType.UNDEFINED
                value_y_value_0_type = runtimeType(value_y_value_0)
                if (RuntimeType.STRING == value_y_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_y_value_0_0  = value_y_value_0 as string
                    valueSerializer.writeString(value_y_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_y_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_y_value_0_1  = value_y_value_0 as number
                    valueSerializer.writeNumber(value_y_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_y_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_y_value_0_2  = value_y_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_y_value_0_2)
                }
            }
            else if (TypeChecker.isGridRowSizeOption(value_y_value, false, false, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_y_value_1  = value_y_value as GridRowSizeOption
                GridRowSizeOption_serializer.write(valueSerializer, value_y_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): GutterOption {
        let valueDeserializer : DeserializerBase = buffer
        const x_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let x_buf : Length | GridRowSizeOption | undefined
        if ((x_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const x_buf__selector : int32 = valueDeserializer.readInt8()
            let x_buf_ : Length | GridRowSizeOption | undefined
            if (x_buf__selector == (0).toChar()) {
                const x_buf__u_selector : int32 = valueDeserializer.readInt8()
                let x_buf__u : string | number | Resource | undefined
                if (x_buf__u_selector == (0).toChar()) {
                    x_buf__u = (valueDeserializer.readString() as string)
                }
                else if (x_buf__u_selector == (1).toChar()) {
                    x_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (x_buf__u_selector == (2).toChar()) {
                    x_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for x_buf__u has to be chosen through deserialisation.")
                }
                x_buf_ = (x_buf__u as string | number | Resource)
            }
            else if (x_buf__selector == (1).toChar()) {
                x_buf_ = GridRowSizeOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for x_buf_ has to be chosen through deserialisation.")
            }
            x_buf = (x_buf_ as Length | GridRowSizeOption)
        }
        const x_result : Length | GridRowSizeOption | undefined = x_buf
        const y_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let y_buf : Length | GridRowSizeOption | undefined
        if ((y_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const y_buf__selector : int32 = valueDeserializer.readInt8()
            let y_buf_ : Length | GridRowSizeOption | undefined
            if (y_buf__selector == (0).toChar()) {
                const y_buf__u_selector : int32 = valueDeserializer.readInt8()
                let y_buf__u : string | number | Resource | undefined
                if (y_buf__u_selector == (0).toChar()) {
                    y_buf__u = (valueDeserializer.readString() as string)
                }
                else if (y_buf__u_selector == (1).toChar()) {
                    y_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (y_buf__u_selector == (2).toChar()) {
                    y_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for y_buf__u has to be chosen through deserialisation.")
                }
                y_buf_ = (y_buf__u as string | number | Resource)
            }
            else if (y_buf__selector == (1).toChar()) {
                y_buf_ = GridRowSizeOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for y_buf_ has to be chosen through deserialisation.")
            }
            y_buf = (y_buf_ as Length | GridRowSizeOption)
        }
        const y_result : Length | GridRowSizeOption | undefined = y_buf
        let value : GutterOption = ({x: x_result, y: y_result} as GutterOption)
        return value
    }
}
export class GridRowOptions_serializer {
    public static write(buffer: SerializerBase, value: GridRowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_gutter  = value.gutter
        let value_gutter_type : int32 = RuntimeType.UNDEFINED
        value_gutter_type = runtimeType(value_gutter)
        valueSerializer.writeInt8((value_gutter_type).toChar())
        if ((value_gutter_type) != (RuntimeType.UNDEFINED)) {
            const value_gutter_value  = value_gutter!
            let value_gutter_value_type : int32 = RuntimeType.UNDEFINED
            value_gutter_value_type = runtimeType(value_gutter_value)
            if ((RuntimeType.STRING == value_gutter_value_type) || (RuntimeType.NUMBER == value_gutter_value_type) || (RuntimeType.OBJECT == value_gutter_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_gutter_value_0  = value_gutter_value as Length
                let value_gutter_value_0_type : int32 = RuntimeType.UNDEFINED
                value_gutter_value_0_type = runtimeType(value_gutter_value_0)
                if (RuntimeType.STRING == value_gutter_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_gutter_value_0_0  = value_gutter_value_0 as string
                    valueSerializer.writeString(value_gutter_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_gutter_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_gutter_value_0_1  = value_gutter_value_0 as number
                    valueSerializer.writeNumber(value_gutter_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_gutter_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_gutter_value_0_2  = value_gutter_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_gutter_value_0_2)
                }
            }
            else if (TypeChecker.isGutterOption(value_gutter_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_gutter_value_1  = value_gutter_value as GutterOption
                GutterOption_serializer.write(valueSerializer, value_gutter_value_1)
            }
        }
        const value_columns  = value.columns
        let value_columns_type : int32 = RuntimeType.UNDEFINED
        value_columns_type = runtimeType(value_columns)
        valueSerializer.writeInt8((value_columns_type).toChar())
        if ((value_columns_type) != (RuntimeType.UNDEFINED)) {
            const value_columns_value  = value_columns!
            let value_columns_value_type : int32 = RuntimeType.UNDEFINED
            value_columns_value_type = runtimeType(value_columns_value)
            if (RuntimeType.NUMBER == value_columns_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_columns_value_0  = value_columns_value as number
                valueSerializer.writeNumber(value_columns_value_0)
            }
            else if (RuntimeType.OBJECT == value_columns_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_columns_value_1  = value_columns_value as GridRowColumnOption
                GridRowColumnOption_serializer.write(valueSerializer, value_columns_value_1)
            }
        }
        const value_breakpoints  = value.breakpoints
        let value_breakpoints_type : int32 = RuntimeType.UNDEFINED
        value_breakpoints_type = runtimeType(value_breakpoints)
        valueSerializer.writeInt8((value_breakpoints_type).toChar())
        if ((value_breakpoints_type) != (RuntimeType.UNDEFINED)) {
            const value_breakpoints_value  = value_breakpoints!
            BreakPoints_serializer.write(valueSerializer, value_breakpoints_value)
        }
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8((value_direction_type).toChar())
        if ((value_direction_type) != (RuntimeType.UNDEFINED)) {
            const value_direction_value  = (value_direction as GridRowDirection)
            valueSerializer.writeInt32(TypeChecker.GridRowDirection_ToNumeric(value_direction_value))
        }
    }
    public static read(buffer: DeserializerBase): GridRowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const gutter_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gutter_buf : Length | GutterOption | undefined
        if ((gutter_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const gutter_buf__selector : int32 = valueDeserializer.readInt8()
            let gutter_buf_ : Length | GutterOption | undefined
            if (gutter_buf__selector == (0).toChar()) {
                const gutter_buf__u_selector : int32 = valueDeserializer.readInt8()
                let gutter_buf__u : string | number | Resource | undefined
                if (gutter_buf__u_selector == (0).toChar()) {
                    gutter_buf__u = (valueDeserializer.readString() as string)
                }
                else if (gutter_buf__u_selector == (1).toChar()) {
                    gutter_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (gutter_buf__u_selector == (2).toChar()) {
                    gutter_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for gutter_buf__u has to be chosen through deserialisation.")
                }
                gutter_buf_ = (gutter_buf__u as string | number | Resource)
            }
            else if (gutter_buf__selector == (1).toChar()) {
                gutter_buf_ = GutterOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for gutter_buf_ has to be chosen through deserialisation.")
            }
            gutter_buf = (gutter_buf_ as Length | GutterOption)
        }
        const gutter_result : Length | GutterOption | undefined = gutter_buf
        const columns_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columns_buf : number | GridRowColumnOption | undefined
        if ((columns_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const columns_buf__selector : int32 = valueDeserializer.readInt8()
            let columns_buf_ : number | GridRowColumnOption | undefined
            if (columns_buf__selector == (0).toChar()) {
                columns_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (columns_buf__selector == (1).toChar()) {
                columns_buf_ = GridRowColumnOption_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for columns_buf_ has to be chosen through deserialisation.")
            }
            columns_buf = (columns_buf_ as number | GridRowColumnOption)
        }
        const columns_result : number | GridRowColumnOption | undefined = columns_buf
        const breakpoints_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let breakpoints_buf : BreakPoints | undefined
        if ((breakpoints_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            breakpoints_buf = BreakPoints_serializer.read(valueDeserializer)
        }
        const breakpoints_result : BreakPoints | undefined = breakpoints_buf
        const direction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let direction_buf : GridRowDirection | undefined
        if ((direction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            direction_buf = TypeChecker.GridRowDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : GridRowDirection | undefined = direction_buf
        let value : GridRowOptions = ({gutter: gutter_result, columns: columns_result, breakpoints: breakpoints_result, direction: direction_result} as GridRowOptions)
        return value
    }
}

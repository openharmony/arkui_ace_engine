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
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonShapeMethodSet, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Length } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRectPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Rect_construct(peerId, flags)
        const _peer  = new ArkRectPeer(_peerPtr, peerId, "Rect", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRectOptionsAttribute(options?: RectOptions | RoundedRectOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            let options_value_type : int32 = RuntimeType.UNDEFINED
            options_value_type = runtimeType(options_value)
            if (TypeChecker.isRectOptions(options_value, false, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const options_value_0  = options_value as RectOptions
                RectOptions_serializer.write(thisSerializer, options_value_0)
            }
            else if (TypeChecker.isRoundedRectOptions(options_value)) {
                thisSerializer.writeInt8((1).toChar())
                const options_value_1  = options_value as RoundedRectOptions
                RoundedRectOptions_serializer.write(thisSerializer, options_value_1)
            }
        }
        ArkUIGeneratedNativeModule._RectInterface_setRectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusAttribute(value: number | string | Array<number | string> | undefined): void {
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
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Array<number | string>
                thisSerializer.writeInt32((value_value_2.length).toInt())
                for (let value_value_2_counter_i = 0; value_value_2_counter_i < value_value_2.length; value_value_2_counter_i++) {
                    const value_value_2_element : number | string = value_value_2[value_value_2_counter_i]
                    let value_value_2_element_type : int32 = RuntimeType.UNDEFINED
                    value_value_2_element_type = runtimeType(value_value_2_element)
                    if (RuntimeType.NUMBER == value_value_2_element_type) {
                        thisSerializer.writeInt8((0).toChar())
                        const value_value_2_element_0  = value_value_2_element as number
                        thisSerializer.writeNumber(value_value_2_element_0)
                    }
                    else if (RuntimeType.STRING == value_value_2_element_type) {
                        thisSerializer.writeInt8((1).toChar())
                        const value_value_2_element_1  = value_value_2_element as string
                        thisSerializer.writeString(value_value_2_element_1)
                    }
                }
            }
        }
        ArkUIGeneratedNativeModule._RectAttribute_setRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type RadiusItem = [
    Length,
    Length
]
export interface RectOptions {
    width?: Length;
    height?: Length;
    radius?: Length | Array<RadiusItem>;
}
export interface RoundedRectOptions {
}
export interface RectAttribute extends CommonShapeMethod {
    radius(value: number | string | Array<number | string> | undefined): this {
        throw new Error("Unimplemented method radius")
    }
    attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRectStyle extends ArkCommonShapeMethodStyle implements RectAttribute {
    radius_value?: number | string | Array<number | string> | undefined
    attributeModifier_value?: AttributeModifier<RectAttribute> | AttributeModifier<CommonMethod> | undefined
    public radius(value: number | string | Array<number | string> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RectAttribute): void {
        super.apply(target)
        if (this.radius_value !== undefined)
            target.radius(this.radius_value!)
    }
}

export class ArkRectComponent extends ArkCommonShapeMethodComponent implements RectAttribute {
    getPeer(): ArkRectPeer {
        return (this.peer as ArkRectPeer)
    }
    public setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        if (this.checkPriority("setRectOptions")) {
            const options_casted = options as (RectOptions | RoundedRectOptions | undefined)
            this.getPeer()?.setRectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public radius(value: number | string | Array<number | string> | undefined): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (number | string | Array<number | string> | undefined)
            this.getPeer()?.setRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRectStyle(receiver: RectAttribute, modifier: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRectStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Rect")
// export function Rect(
//     options?: RectOptions | RoundedRectOptions,
//     @memo
//     content_?: () => void,
// ): RectAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Rect(
    @memo
    style: ((attributes: RectAttribute) => void) | undefined,
    options?: RectOptions | RoundedRectOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRectComponent>((): ArkRectComponent => {
        return new ArkRectComponent()
    })
    NodeAttach<ArkRectPeer>((): ArkRectPeer => ArkRectPeer.create(receiver), (_: ArkRectPeer): void => {
        receiver.setRectOptions(options)
        style?.(receiver)
        withRectStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRectSet extends ArkCommonShapeMethodSet implements RectAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _radius_flag?: boolean
    _radius0_value?: number | string | Array<number | string> | undefined
    applyModifierPatch(component: RectAttribute): void {
        if (this._radius_flag)
            component.radius((this._radius0_value as number | string | Array<number | string> | undefined))
    }
    public radius(value: number | string | Array<number | string> | undefined): this {
        this._radius_flag = true
        this._radius0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RoundedRectOptions_serializer {
    public static write(buffer: SerializerBase, value: RoundedRectOptions): void {
    }
    public static read(buffer: DeserializerBase): RoundedRectOptions {
        let value : RoundedRectOptions = ({} as RoundedRectOptions)
        return value
    }
}
export class RectOptions_serializer {
    public static write(buffer: SerializerBase, value: RectOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as string
                valueSerializer.writeString(value_width_value_0)
            }
            else if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_1)
            }
            else if (RuntimeType.OBJECT == value_width_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_width_value_2  = value_width_value as Resource
                Resource_serializer.write(valueSerializer, value_width_value_2)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as string
                valueSerializer.writeString(value_height_value_0)
            }
            else if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_1)
            }
            else if (RuntimeType.OBJECT == value_height_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_height_value_2  = value_height_value as Resource
                Resource_serializer.write(valueSerializer, value_height_value_2)
            }
        }
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8((value_radius_type).toChar())
        if ((value_radius_type) != (RuntimeType.UNDEFINED)) {
            const value_radius_value  = value_radius!
            let value_radius_value_type : int32 = RuntimeType.UNDEFINED
            value_radius_value_type = runtimeType(value_radius_value)
            if ((RuntimeType.STRING == value_radius_value_type) || (RuntimeType.NUMBER == value_radius_value_type) || (RuntimeType.OBJECT == value_radius_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_radius_value_0  = value_radius_value as Length
                let value_radius_value_0_type : int32 = RuntimeType.UNDEFINED
                value_radius_value_0_type = runtimeType(value_radius_value_0)
                if (RuntimeType.STRING == value_radius_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_radius_value_0_0  = value_radius_value_0 as string
                    valueSerializer.writeString(value_radius_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_radius_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_radius_value_0_1  = value_radius_value_0 as number
                    valueSerializer.writeNumber(value_radius_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_radius_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_radius_value_0_2  = value_radius_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_radius_value_0_2)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_radius_value_type)) && (TypeChecker.isArray_RadiusItem(value_radius_value))) {
                valueSerializer.writeInt8((1).toChar())
                const value_radius_value_1  = value_radius_value as Array<RadiusItem>
                valueSerializer.writeInt32((value_radius_value_1.length).toInt())
                for (let value_radius_value_1_counter_i = 0; value_radius_value_1_counter_i < value_radius_value_1.length; value_radius_value_1_counter_i++) {
                    const value_radius_value_1_element : RadiusItem = value_radius_value_1[value_radius_value_1_counter_i]
                    const value_radius_value_1_element_0  = value_radius_value_1_element[0]
                    let value_radius_value_1_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_radius_value_1_element_0_type = runtimeType(value_radius_value_1_element_0)
                    if (RuntimeType.STRING == value_radius_value_1_element_0_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_radius_value_1_element_0_0  = value_radius_value_1_element_0 as string
                        valueSerializer.writeString(value_radius_value_1_element_0_0)
                    }
                    else if (RuntimeType.NUMBER == value_radius_value_1_element_0_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_radius_value_1_element_0_1  = value_radius_value_1_element_0 as number
                        valueSerializer.writeNumber(value_radius_value_1_element_0_1)
                    }
                    else if (RuntimeType.OBJECT == value_radius_value_1_element_0_type) {
                        valueSerializer.writeInt8((2).toChar())
                        const value_radius_value_1_element_0_2  = value_radius_value_1_element_0 as Resource
                        Resource_serializer.write(valueSerializer, value_radius_value_1_element_0_2)
                    }
                    const value_radius_value_1_element_1  = value_radius_value_1_element[1]
                    let value_radius_value_1_element_1_type : int32 = RuntimeType.UNDEFINED
                    value_radius_value_1_element_1_type = runtimeType(value_radius_value_1_element_1)
                    if (RuntimeType.STRING == value_radius_value_1_element_1_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_radius_value_1_element_1_0  = value_radius_value_1_element_1 as string
                        valueSerializer.writeString(value_radius_value_1_element_1_0)
                    }
                    else if (RuntimeType.NUMBER == value_radius_value_1_element_1_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_radius_value_1_element_1_1  = value_radius_value_1_element_1 as number
                        valueSerializer.writeNumber(value_radius_value_1_element_1_1)
                    }
                    else if (RuntimeType.OBJECT == value_radius_value_1_element_1_type) {
                        valueSerializer.writeInt8((2).toChar())
                        const value_radius_value_1_element_1_2  = value_radius_value_1_element_1 as Resource
                        Resource_serializer.write(valueSerializer, value_radius_value_1_element_1_2)
                    }
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): RectOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : Length | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | Resource | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (2).toChar()) {
                width_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number | Resource)
        }
        const width_result : Length | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : Length | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : string | number | Resource | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (2).toChar()) {
                height_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as string | number | Resource)
        }
        const height_result : Length | undefined = height_buf
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : Length | Array<RadiusItem> | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : Length | Array<RadiusItem> | undefined
            if (radius_buf__selector == (0).toChar()) {
                const radius_buf__u_selector : int32 = valueDeserializer.readInt8()
                let radius_buf__u : string | number | Resource | undefined
                if (radius_buf__u_selector == (0).toChar()) {
                    radius_buf__u = (valueDeserializer.readString() as string)
                }
                else if (radius_buf__u_selector == (1).toChar()) {
                    radius_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (radius_buf__u_selector == (2).toChar()) {
                    radius_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for radius_buf__u has to be chosen through deserialisation.")
                }
                radius_buf_ = (radius_buf__u as string | number | Resource)
            }
            else if (radius_buf__selector == (1).toChar()) {
                const radius_buf__u_length : int32 = valueDeserializer.readInt32()
                let radius_buf__u : Array<RadiusItem> = new Array<RadiusItem>(radius_buf__u_length)
                for (let radius_buf__u_i = 0; radius_buf__u_i < radius_buf__u_length; radius_buf__u_i++) {
                    const radius_buf__u_buf_value0_buf_selector : int32 = valueDeserializer.readInt8()
                    let radius_buf__u_buf_value0_buf : string | number | Resource | undefined
                    if (radius_buf__u_buf_value0_buf_selector == (0).toChar()) {
                        radius_buf__u_buf_value0_buf = (valueDeserializer.readString() as string)
                    }
                    else if (radius_buf__u_buf_value0_buf_selector == (1).toChar()) {
                        radius_buf__u_buf_value0_buf = (valueDeserializer.readNumber() as number)
                    }
                    else if (radius_buf__u_buf_value0_buf_selector == (2).toChar()) {
                        radius_buf__u_buf_value0_buf = Resource_serializer.read(valueDeserializer)
                    }
                    else {
                        throw new Error("One of the branches for radius_buf__u_buf_value0_buf has to be chosen through deserialisation.")
                    }
                    const radius_buf__u_buf_value0 : Length = (radius_buf__u_buf_value0_buf as string | number | Resource)
                    const radius_buf__u_buf_value1_buf_selector : int32 = valueDeserializer.readInt8()
                    let radius_buf__u_buf_value1_buf : string | number | Resource | undefined
                    if (radius_buf__u_buf_value1_buf_selector == (0).toChar()) {
                        radius_buf__u_buf_value1_buf = (valueDeserializer.readString() as string)
                    }
                    else if (radius_buf__u_buf_value1_buf_selector == (1).toChar()) {
                        radius_buf__u_buf_value1_buf = (valueDeserializer.readNumber() as number)
                    }
                    else if (radius_buf__u_buf_value1_buf_selector == (2).toChar()) {
                        radius_buf__u_buf_value1_buf = Resource_serializer.read(valueDeserializer)
                    }
                    else {
                        throw new Error("One of the branches for radius_buf__u_buf_value1_buf has to be chosen through deserialisation.")
                    }
                    const radius_buf__u_buf_value1 : Length = (radius_buf__u_buf_value1_buf as string | number | Resource)
                    radius_buf__u[radius_buf__u_i] = ([radius_buf__u_buf_value0, radius_buf__u_buf_value1] as RadiusItem)
                }
                radius_buf_ = radius_buf__u
            }
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as Length | Array<RadiusItem>)
        }
        const radius_result : Length | Array<RadiusItem> | undefined = radius_buf
        let value : RectOptions = ({width: width_result, height: height_result, radius: radius_result} as RectOptions)
        return value
    }
}

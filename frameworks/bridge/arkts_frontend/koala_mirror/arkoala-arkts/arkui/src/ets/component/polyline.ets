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
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonShapeMethodSet, ArkCommonMethodSet } from "./common"
import { ShapePoint } from "./line"
import { Length } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkPolylinePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPolylinePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Polyline_construct(peerId, flags)
        const _peer  = new ArkPolylinePeer(_peerPtr, peerId, "Polyline", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPolylineOptionsAttribute(options?: PolylineOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            PolylineOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._PolylineInterface_setPolylineOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointsAttribute(value: Array<ShapePoint> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ShapePoint = value_value[value_value_counter_i]
                const value_value_element_0  = value_value_element[0]
                let value_value_element_0_type : int32 = RuntimeType.UNDEFINED
                value_value_element_0_type = runtimeType(value_value_element_0)
                if (RuntimeType.STRING == value_value_element_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_element_0_0  = value_value_element_0 as string
                    thisSerializer.writeString(value_value_element_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_element_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_element_0_1  = value_value_element_0 as number
                    thisSerializer.writeNumber(value_value_element_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_element_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_element_0_2  = value_value_element_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_element_0_2)
                }
                const value_value_element_1  = value_value_element[1]
                let value_value_element_1_type : int32 = RuntimeType.UNDEFINED
                value_value_element_1_type = runtimeType(value_value_element_1)
                if (RuntimeType.STRING == value_value_element_1_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_element_1_0  = value_value_element_1 as string
                    thisSerializer.writeString(value_value_element_1_0)
                }
                else if (RuntimeType.NUMBER == value_value_element_1_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_element_1_1  = value_value_element_1 as number
                    thisSerializer.writeNumber(value_value_element_1_1)
                }
                else if (RuntimeType.OBJECT == value_value_element_1_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_element_1_2  = value_value_element_1 as Resource
                    Resource_serializer.write(thisSerializer, value_value_element_1_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._PolylineAttribute_setPoints(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PolylineOptions {
    width?: string | number;
    height?: string | number;
}
export interface PolylineAttribute extends CommonShapeMethod {
    points(value: Array<ShapePoint> | undefined): this {
        throw new Error("Unimplemented method points")
    }
    attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkPolylineStyle extends ArkCommonShapeMethodStyle implements PolylineAttribute {
    points_value?: Array<ShapePoint> | undefined
    attributeModifier_value?: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonMethod> | undefined
    public points(value: Array<ShapePoint> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: PolylineAttribute): void {
        super.apply(target)
        if (this.points_value !== undefined)
            target.points(this.points_value!)
    }
}

export class ArkPolylineComponent extends ArkCommonShapeMethodComponent implements PolylineAttribute {
    getPeer(): ArkPolylinePeer {
        return (this.peer as ArkPolylinePeer)
    }
    public setPolylineOptions(options?: PolylineOptions): this {
        if (this.checkPriority("setPolylineOptions")) {
            const options_casted = options as (PolylineOptions | undefined)
            this.getPeer()?.setPolylineOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public points(value: Array<ShapePoint> | undefined): this {
        if (this.checkPriority("points")) {
            const value_casted = value as (Array<ShapePoint> | undefined)
            this.getPeer()?.setPointsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withPolylineStyle(receiver: PolylineAttribute, modifier: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkPolylineStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Polyline")
// export function Polyline(
//     options?: PolylineOptions,
//     @memo
//     content_?: () => void,
// ): PolylineAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Polyline(
    @memo
    style: ((attributes: PolylineAttribute) => void) | undefined,
    options?: PolylineOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPolylineComponent>((): ArkPolylineComponent => {
        return new ArkPolylineComponent()
    })
    NodeAttach<ArkPolylinePeer>((): ArkPolylinePeer => ArkPolylinePeer.create(receiver), (_: ArkPolylinePeer): void => {
        receiver.setPolylineOptions(options)
        style?.(receiver)
        withPolylineStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkPolylineSet extends ArkCommonShapeMethodSet implements PolylineAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _points_flag?: boolean
    _points0_value?: Array<ShapePoint> | undefined
    applyModifierPatch(component: PolylineAttribute): void {
        if (this._points_flag)
            component.points((this._points0_value as Array<ShapePoint> | undefined))
    }
    public points(value: Array<ShapePoint> | undefined): this {
        this._points_flag = true
        this._points0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class PolylineOptions_serializer {
    public static write(buffer: SerializerBase, value: PolylineOptions): void {
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
        }
    }
    public static read(buffer: DeserializerBase): PolylineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : string | number | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number)
        }
        const width_result : string | number | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : string | number | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : string | number | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as string | number)
        }
        const height_result : string | number | undefined = height_buf
        let value : PolylineOptions = ({width: width_result, height: height_result} as PolylineOptions)
        return value
    }
}

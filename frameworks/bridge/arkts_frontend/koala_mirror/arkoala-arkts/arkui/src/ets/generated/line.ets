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
import { Resource_serializer, Resource } from "./resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Length } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkLinePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLinePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Line_construct(peerId, flags)
        const _peer  = new ArkLinePeer(_peerPtr, peerId, "Line", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLineOptionsAttribute(options?: LineOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            LineOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._LineInterface_setLineOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    startPointAttribute(value: ShapePoint | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            let value_value_0_type : int32 = RuntimeType.UNDEFINED
            value_value_0_type = runtimeType(value_value_0)
            if (RuntimeType.STRING == value_value_0_type) {
                thisSerializer.writeInt8(0)
                const value_value_0_0  = value_value_0 as string
                thisSerializer.writeString(value_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_value_0_type) {
                thisSerializer.writeInt8(1)
                const value_value_0_1  = value_value_0 as number
                thisSerializer.writeNumber(value_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_value_0_type) {
                thisSerializer.writeInt8(2)
                const value_value_0_2  = value_value_0 as Resource
                Resource_serializer.write(thisSerializer, value_value_0_2)
            }
            const value_value_1  = value_value[1]
            let value_value_1_type : int32 = RuntimeType.UNDEFINED
            value_value_1_type = runtimeType(value_value_1)
            if (RuntimeType.STRING == value_value_1_type) {
                thisSerializer.writeInt8(0)
                const value_value_1_0  = value_value_1 as string
                thisSerializer.writeString(value_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_value_1_type) {
                thisSerializer.writeInt8(1)
                const value_value_1_1  = value_value_1 as number
                thisSerializer.writeNumber(value_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_value_1_type) {
                thisSerializer.writeInt8(2)
                const value_value_1_2  = value_value_1 as Resource
                Resource_serializer.write(thisSerializer, value_value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._LineAttribute_startPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    endPointAttribute(value: ShapePoint | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            let value_value_0_type : int32 = RuntimeType.UNDEFINED
            value_value_0_type = runtimeType(value_value_0)
            if (RuntimeType.STRING == value_value_0_type) {
                thisSerializer.writeInt8(0)
                const value_value_0_0  = value_value_0 as string
                thisSerializer.writeString(value_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_value_0_type) {
                thisSerializer.writeInt8(1)
                const value_value_0_1  = value_value_0 as number
                thisSerializer.writeNumber(value_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_value_0_type) {
                thisSerializer.writeInt8(2)
                const value_value_0_2  = value_value_0 as Resource
                Resource_serializer.write(thisSerializer, value_value_0_2)
            }
            const value_value_1  = value_value[1]
            let value_value_1_type : int32 = RuntimeType.UNDEFINED
            value_value_1_type = runtimeType(value_value_1)
            if (RuntimeType.STRING == value_value_1_type) {
                thisSerializer.writeInt8(0)
                const value_value_1_0  = value_value_1 as string
                thisSerializer.writeString(value_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_value_1_type) {
                thisSerializer.writeInt8(1)
                const value_value_1_1  = value_value_1 as number
                thisSerializer.writeNumber(value_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_value_1_type) {
                thisSerializer.writeInt8(2)
                const value_value_1_2  = value_value_1 as Resource
                Resource_serializer.write(thisSerializer, value_value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._LineAttribute_endPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type ShapePoint = [
    Length,
    Length
]
export interface LineOptions {
    width?: string | number;
    height?: string | number;
}
export interface LineAttribute extends CommonShapeMethod {
    startPoint(value: ShapePoint | undefined): this
    endPoint(value: ShapePoint | undefined): this
    attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkLineStyle extends ArkCommonShapeMethodStyle implements LineAttribute {
    startPoint_value?: ShapePoint | undefined
    endPoint_value?: ShapePoint | undefined
    attributeModifier_value?: AttributeModifier<LineAttribute> | AttributeModifier<CommonMethod> | undefined
    public startPoint(value: ShapePoint | undefined): this {
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: LineAttribute): void {
        super.apply(target)
        if (this.startPoint_value !== undefined)
            target.startPoint(this.startPoint_value!)
        if (this.endPoint_value !== undefined)
            target.endPoint(this.endPoint_value!)
    }
}

export class ArkLineComponent extends ArkCommonShapeMethodComponent implements LineAttribute {
    getPeer(): ArkLinePeer {
        return (this.peer as ArkLinePeer)
    }
    public setLineOptions(options?: LineOptions): this {
        if (this.checkPriority("setLineOptions")) {
            const options_casted = options as (LineOptions | undefined)
            this.getPeer()?.setLineOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public startPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority("startPoint")) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.startPointAttribute(value_casted)
            return this
        }
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority("endPoint")) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.endPointAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withLineStyle(receiver: LineAttribute, modifier: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkLineStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("LineImpl")
export function Line(
    options?: LineOptions | undefined,
    @memo
    content_?: () => void,
): LineAttribute {
    throw new Error("Not implemented")
}

@memo
export function LineImpl(
    @memo
    style: ((attributes: LineAttribute) => void) | undefined,
    options?: LineOptions | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLineComponent>((): ArkLineComponent => {
        return new ArkLineComponent()
    })
    NodeAttach<ArkLinePeer>((): ArkLinePeer => ArkLinePeer.create(receiver), (_: ArkLinePeer): void => {
        receiver.setLineOptions(options)
        style?.(receiver)
        withLineStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class LineOptions_serializer {
    public static write(buffer: SerializerBase, value: LineOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8(value_width_type)
        if ((RuntimeType.UNDEFINED) != (value_width_type)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8(0)
                const value_width_value_0  = value_width_value as string
                valueSerializer.writeString(value_width_value_0)
            }
            else if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8(1)
                const value_width_value_1  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8(value_height_type)
        if ((RuntimeType.UNDEFINED) != (value_height_type)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8(0)
                const value_height_value_0  = value_height_value as string
                valueSerializer.writeString(value_height_value_0)
            }
            else if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8(1)
                const value_height_value_1  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): LineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let width_buf : string | number | undefined
        if ((RuntimeType.UNDEFINED) != (width_buf_runtimeType))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | undefined
            if (width_buf__selector == 0) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == 1) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number)
        }
        const width_result : string | number | undefined = width_buf
        const height_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let height_buf : string | number | undefined
        if ((RuntimeType.UNDEFINED) != (height_buf_runtimeType))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : string | number | undefined
            if (height_buf__selector == 0) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else if (height_buf__selector == 1) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as string | number)
        }
        const height_result : string | number | undefined = height_buf
        let value : LineOptions = ({width: width_result, height: height_result} as LineOptions)
        return value
    }
}

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
import { Length } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            LineOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._LineInterface_setLineOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStartPointAttribute(value: ShapePoint | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            let value_value_0_type : int32 = RuntimeType.UNDEFINED
            value_value_0_type = runtimeType(value_value_0)
            if (RuntimeType.STRING == value_value_0_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0_0  = value_value_0 as string
                thisSerializer.writeString(value_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_value_0_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_0_1  = value_value_0 as number
                thisSerializer.writeNumber(value_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_value_0_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_0_2  = value_value_0 as Resource
                Resource_serializer.write(thisSerializer, value_value_0_2)
            }
            const value_value_1  = value_value[1]
            let value_value_1_type : int32 = RuntimeType.UNDEFINED
            value_value_1_type = runtimeType(value_value_1)
            if (RuntimeType.STRING == value_value_1_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_1_0  = value_value_1 as string
                thisSerializer.writeString(value_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_value_1_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1_1  = value_value_1 as number
                thisSerializer.writeNumber(value_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_value_1_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_1_2  = value_value_1 as Resource
                Resource_serializer.write(thisSerializer, value_value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._LineAttribute_setStartPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEndPointAttribute(value: ShapePoint | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            let value_value_0_type : int32 = RuntimeType.UNDEFINED
            value_value_0_type = runtimeType(value_value_0)
            if (RuntimeType.STRING == value_value_0_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0_0  = value_value_0 as string
                thisSerializer.writeString(value_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_value_0_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_0_1  = value_value_0 as number
                thisSerializer.writeNumber(value_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_value_0_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_0_2  = value_value_0 as Resource
                Resource_serializer.write(thisSerializer, value_value_0_2)
            }
            const value_value_1  = value_value[1]
            let value_value_1_type : int32 = RuntimeType.UNDEFINED
            value_value_1_type = runtimeType(value_value_1)
            if (RuntimeType.STRING == value_value_1_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_1_0  = value_value_1 as string
                thisSerializer.writeString(value_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_value_1_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1_1  = value_value_1 as number
                thisSerializer.writeNumber(value_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_value_1_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_1_2  = value_value_1 as Resource
                Resource_serializer.write(thisSerializer, value_value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._LineAttribute_setEndPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type ShapePoint = [
    Length,
    Length
]
export interface LineOptions {
}
export interface LineAttribute extends CommonShapeMethod {
    startPoint(value: ShapePoint | undefined): this {
        throw new Error("Unimplemented method startPoint")
    }
    endPoint(value: ShapePoint | undefined): this {
        throw new Error("Unimplemented method endPoint")
    }
    attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
            this.getPeer()?.setStartPointAttribute(value_casted)
            return this
        }
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority("endPoint")) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.setEndPointAttribute(value_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Line")
// export function Line(
//     options?: LineOptions,
//     @memo
//     content_?: () => void,
// ): LineAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Line(
    @memo
    style: ((attributes: LineAttribute) => void) | undefined,
    options?: LineOptions,
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

export class ArkLineSet extends ArkCommonShapeMethodSet implements LineAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _startPoint_flag?: boolean
    _startPoint0_value?: ShapePoint | undefined
    _endPoint_flag?: boolean
    _endPoint0_value?: ShapePoint | undefined
    applyModifierPatch(component: LineAttribute): void {
        if (this._startPoint_flag)
            component.startPoint((this._startPoint0_value as ShapePoint | undefined))
        if (this._endPoint_flag)
            component.endPoint((this._endPoint0_value as ShapePoint | undefined))
    }
    public startPoint(value: ShapePoint | undefined): this {
        this._startPoint_flag = true
        this._startPoint0_value = value
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        this._endPoint_flag = true
        this._endPoint0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class LineOptions_serializer {
    public static write(buffer: SerializerBase, value: LineOptions): void {
    }
    public static read(buffer: DeserializerBase): LineOptions {
        let value : LineOptions = ({} as LineOptions)
        return value
    }
}

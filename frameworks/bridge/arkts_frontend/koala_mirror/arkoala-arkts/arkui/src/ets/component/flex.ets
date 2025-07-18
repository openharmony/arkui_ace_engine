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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { FlexDirection, FlexWrap, FlexAlign, ItemAlign } from "./enums"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFlexPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFlexPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Flex_construct(peerId, flags)
        const _peer  = new ArkFlexPeer(_peerPtr, peerId, "Flex", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFlexOptionsAttribute(value?: FlexOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            FlexOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._FlexInterface_setFlexOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PointLightStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._FlexAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface FlexOptions {
    direction?: FlexDirection;
    wrap?: FlexWrap;
    justifyContent?: FlexAlign;
    alignItems?: ItemAlign;
    alignContent?: FlexAlign;
    space?: FlexSpaceOptions;
}
export interface FlexSpaceOptions {
    main?: LengthMetrics;
    cross?: LengthMetrics;
}
export interface FlexAttribute extends CommonMethod {
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error("Unimplemented method pointLight")
    }
    attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFlexStyle extends ArkCommonMethodStyle implements FlexAttribute {
    pointLight_value?: PointLightStyle | undefined
    attributeModifier_value?: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: FlexAttribute): void {
        super.apply(target)
        if (this.pointLight_value !== undefined)
            target.pointLight(this.pointLight_value!)
    }
}

export class ArkFlexComponent extends ArkCommonMethodComponent implements FlexAttribute {
    getPeer(): ArkFlexPeer {
        return (this.peer as ArkFlexPeer)
    }
    public setFlexOptions(value?: FlexOptions): this {
        if (this.checkPriority("setFlexOptions")) {
            const value_casted = value as (FlexOptions | undefined)
            this.getPeer()?.setFlexOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withFlexStyle(receiver: FlexAttribute, modifier: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkFlexStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Flex")
// export function Flex(
//     value?: FlexOptions,
//     @memo
//     content_?: () => void,
// ): FlexAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Flex(
    @memo
    style: ((attributes: FlexAttribute) => void) | undefined,
    value?: FlexOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFlexComponent>((): ArkFlexComponent => {
        return new ArkFlexComponent()
    })
    NodeAttach<ArkFlexPeer>((): ArkFlexPeer => ArkFlexPeer.create(receiver), (_: ArkFlexPeer): void => {
        receiver.setFlexOptions(value)
        style?.(receiver)
        withFlexStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkFlexSet extends ArkCommonMethodSet implements FlexAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _pointLight_flag?: boolean
    _pointLight0_value?: PointLightStyle | undefined
    applyModifierPatch(component: FlexAttribute): void {
        if (this._pointLight_flag)
            component.pointLight((this._pointLight0_value as PointLightStyle | undefined))
    }
    public pointLight(value: PointLightStyle | undefined): this {
        this._pointLight_flag = true
        this._pointLight0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class FlexSpaceOptions_serializer {
    public static write(buffer: SerializerBase, value: FlexSpaceOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_main  = value.main
        let value_main_type : int32 = RuntimeType.UNDEFINED
        value_main_type = runtimeType(value_main)
        valueSerializer.writeInt8((value_main_type).toChar())
        if ((value_main_type) != (RuntimeType.UNDEFINED)) {
            const value_main_value  = value_main!
            LengthMetrics_serializer.write(valueSerializer, value_main_value)
        }
        const value_cross  = value.cross
        let value_cross_type : int32 = RuntimeType.UNDEFINED
        value_cross_type = runtimeType(value_cross)
        valueSerializer.writeInt8((value_cross_type).toChar())
        if ((value_cross_type) != (RuntimeType.UNDEFINED)) {
            const value_cross_value  = value_cross!
            LengthMetrics_serializer.write(valueSerializer, value_cross_value)
        }
    }
    public static read(buffer: DeserializerBase): FlexSpaceOptions {
        let valueDeserializer : DeserializerBase = buffer
        const main_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let main_buf : LengthMetrics | undefined
        if ((main_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            main_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const main_result : LengthMetrics | undefined = main_buf
        const cross_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cross_buf : LengthMetrics | undefined
        if ((cross_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            cross_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const cross_result : LengthMetrics | undefined = cross_buf
        let value : FlexSpaceOptions = ({main: main_result, cross: cross_result} as FlexSpaceOptions)
        return value
    }
}
export class FlexOptions_serializer {
    public static write(buffer: SerializerBase, value: FlexOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8((value_direction_type).toChar())
        if ((value_direction_type) != (RuntimeType.UNDEFINED)) {
            const value_direction_value  = (value_direction as FlexDirection)
            valueSerializer.writeInt32(TypeChecker.FlexDirection_ToNumeric(value_direction_value))
        }
        const value_wrap  = value.wrap
        let value_wrap_type : int32 = RuntimeType.UNDEFINED
        value_wrap_type = runtimeType(value_wrap)
        valueSerializer.writeInt8((value_wrap_type).toChar())
        if ((value_wrap_type) != (RuntimeType.UNDEFINED)) {
            const value_wrap_value  = (value_wrap as FlexWrap)
            valueSerializer.writeInt32(TypeChecker.FlexWrap_ToNumeric(value_wrap_value))
        }
        const value_justifyContent  = value.justifyContent
        let value_justifyContent_type : int32 = RuntimeType.UNDEFINED
        value_justifyContent_type = runtimeType(value_justifyContent)
        valueSerializer.writeInt8((value_justifyContent_type).toChar())
        if ((value_justifyContent_type) != (RuntimeType.UNDEFINED)) {
            const value_justifyContent_value  = (value_justifyContent as FlexAlign)
            valueSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(value_justifyContent_value))
        }
        const value_alignItems  = value.alignItems
        let value_alignItems_type : int32 = RuntimeType.UNDEFINED
        value_alignItems_type = runtimeType(value_alignItems)
        valueSerializer.writeInt8((value_alignItems_type).toChar())
        if ((value_alignItems_type) != (RuntimeType.UNDEFINED)) {
            const value_alignItems_value  = (value_alignItems as ItemAlign)
            valueSerializer.writeInt32(TypeChecker.ItemAlign_ToNumeric(value_alignItems_value))
        }
        const value_alignContent  = value.alignContent
        let value_alignContent_type : int32 = RuntimeType.UNDEFINED
        value_alignContent_type = runtimeType(value_alignContent)
        valueSerializer.writeInt8((value_alignContent_type).toChar())
        if ((value_alignContent_type) != (RuntimeType.UNDEFINED)) {
            const value_alignContent_value  = (value_alignContent as FlexAlign)
            valueSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(value_alignContent_value))
        }
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8((value_space_type).toChar())
        if ((value_space_type) != (RuntimeType.UNDEFINED)) {
            const value_space_value  = value_space!
            FlexSpaceOptions_serializer.write(valueSerializer, value_space_value)
        }
    }
    public static read(buffer: DeserializerBase): FlexOptions {
        let valueDeserializer : DeserializerBase = buffer
        const direction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let direction_buf : FlexDirection | undefined
        if ((direction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            direction_buf = TypeChecker.FlexDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : FlexDirection | undefined = direction_buf
        const wrap_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wrap_buf : FlexWrap | undefined
        if ((wrap_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            wrap_buf = TypeChecker.FlexWrap_FromNumeric(valueDeserializer.readInt32())
        }
        const wrap_result : FlexWrap | undefined = wrap_buf
        const justifyContent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let justifyContent_buf : FlexAlign | undefined
        if ((justifyContent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            justifyContent_buf = TypeChecker.FlexAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const justifyContent_result : FlexAlign | undefined = justifyContent_buf
        const alignItems_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignItems_buf : ItemAlign | undefined
        if ((alignItems_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            alignItems_buf = TypeChecker.ItemAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const alignItems_result : ItemAlign | undefined = alignItems_buf
        const alignContent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignContent_buf : FlexAlign | undefined
        if ((alignContent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            alignContent_buf = TypeChecker.FlexAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const alignContent_result : FlexAlign | undefined = alignContent_buf
        const space_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let space_buf : FlexSpaceOptions | undefined
        if ((space_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            space_buf = FlexSpaceOptions_serializer.read(valueDeserializer)
        }
        const space_result : FlexSpaceOptions | undefined = space_buf
        let value : FlexOptions = ({direction: direction_result, wrap: wrap_result, justifyContent: justifyContent_result, alignItems: alignItems_result, alignContent: alignContent_result, space: space_result} as FlexOptions)
        return value
    }
}

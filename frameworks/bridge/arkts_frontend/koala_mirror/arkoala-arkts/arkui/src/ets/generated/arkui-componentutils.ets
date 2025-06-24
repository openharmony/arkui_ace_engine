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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Size, Size_serializer } from "./arkui.Graphics"
import { GlobalScope } from "./GlobalScope"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export interface ComponentInfo {
    size: Size;
    localOffset: Offset_componentutils;
    windowOffset: Offset_componentutils;
    screenOffset: Offset_componentutils;
    translate: TranslateResult;
    scale: ScaleResult;
    rotate: RotateResult;
    transform: Matrix4Result;
}
export interface Offset_componentutils {
    x: number;
    y: number;
}
export interface TranslateResult {
    x: number;
    y: number;
    z: number;
}
export interface ScaleResult {
    x: number;
    y: number;
    z: number;
    centerX: number;
    centerY: number;
}
export interface RotateResult {
    x: number;
    y: number;
    z: number;
    centerX: number;
    centerY: number;
    angle: number;
}
export type Matrix4Result = [
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number
]
export function getRectangleById(id: string): ComponentInfo {
    return GlobalScope.getRectangleById(id)
}
export class Offset_componentutils_serializer {
    public static write(buffer: SerializerBase, value: Offset_componentutils): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
    }
    public static read(buffer: DeserializerBase): Offset_componentutils {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        let value : Offset_componentutils = ({x: x_result, y: y_result} as Offset_componentutils)
        return value
    }
}
export class RotateResult_serializer {
    public static write(buffer: SerializerBase, value: RotateResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
        const value_centerX  = value.centerX
        valueSerializer.writeNumber(value_centerX)
        const value_centerY  = value.centerY
        valueSerializer.writeNumber(value_centerY)
        const value_angle  = value.angle
        valueSerializer.writeNumber(value_angle)
    }
    public static read(buffer: DeserializerBase): RotateResult {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        const centerX_result : number = (valueDeserializer.readNumber() as number)
        const centerY_result : number = (valueDeserializer.readNumber() as number)
        const angle_result : number = (valueDeserializer.readNumber() as number)
        let value : RotateResult = ({x: x_result, y: y_result, z: z_result, centerX: centerX_result, centerY: centerY_result, angle: angle_result} as RotateResult)
        return value
    }
}
export class ScaleResult_serializer {
    public static write(buffer: SerializerBase, value: ScaleResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
        const value_centerX  = value.centerX
        valueSerializer.writeNumber(value_centerX)
        const value_centerY  = value.centerY
        valueSerializer.writeNumber(value_centerY)
    }
    public static read(buffer: DeserializerBase): ScaleResult {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        const centerX_result : number = (valueDeserializer.readNumber() as number)
        const centerY_result : number = (valueDeserializer.readNumber() as number)
        let value : ScaleResult = ({x: x_result, y: y_result, z: z_result, centerX: centerX_result, centerY: centerY_result} as ScaleResult)
        return value
    }
}
export class TranslateResult_serializer {
    public static write(buffer: SerializerBase, value: TranslateResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
    }
    public static read(buffer: DeserializerBase): TranslateResult {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        let value : TranslateResult = ({x: x_result, y: y_result, z: z_result} as TranslateResult)
        return value
    }
}
export class ComponentInfo_serializer {
    public static write(buffer: SerializerBase, value: ComponentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_size  = value.size
        Size_serializer.write(valueSerializer, value_size)
        const value_localOffset  = value.localOffset
        Offset_componentutils_serializer.write(valueSerializer, value_localOffset)
        const value_windowOffset  = value.windowOffset
        Offset_componentutils_serializer.write(valueSerializer, value_windowOffset)
        const value_screenOffset  = value.screenOffset
        Offset_componentutils_serializer.write(valueSerializer, value_screenOffset)
        const value_translate  = value.translate
        TranslateResult_serializer.write(valueSerializer, value_translate)
        const value_scale  = value.scale
        ScaleResult_serializer.write(valueSerializer, value_scale)
        const value_rotate  = value.rotate
        RotateResult_serializer.write(valueSerializer, value_rotate)
        const value_transform  = value.transform
        const value_transform_0  = value_transform[0]
        valueSerializer.writeNumber(value_transform_0)
        const value_transform_1  = value_transform[1]
        valueSerializer.writeNumber(value_transform_1)
        const value_transform_2  = value_transform[2]
        valueSerializer.writeNumber(value_transform_2)
        const value_transform_3  = value_transform[3]
        valueSerializer.writeNumber(value_transform_3)
        const value_transform_4  = value_transform[4]
        valueSerializer.writeNumber(value_transform_4)
        const value_transform_5  = value_transform[5]
        valueSerializer.writeNumber(value_transform_5)
        const value_transform_6  = value_transform[6]
        valueSerializer.writeNumber(value_transform_6)
        const value_transform_7  = value_transform[7]
        valueSerializer.writeNumber(value_transform_7)
        const value_transform_8  = value_transform[8]
        valueSerializer.writeNumber(value_transform_8)
        const value_transform_9  = value_transform[9]
        valueSerializer.writeNumber(value_transform_9)
        const value_transform_10  = value_transform[10]
        valueSerializer.writeNumber(value_transform_10)
        const value_transform_11  = value_transform[11]
        valueSerializer.writeNumber(value_transform_11)
        const value_transform_12  = value_transform[12]
        valueSerializer.writeNumber(value_transform_12)
        const value_transform_13  = value_transform[13]
        valueSerializer.writeNumber(value_transform_13)
        const value_transform_14  = value_transform[14]
        valueSerializer.writeNumber(value_transform_14)
        const value_transform_15  = value_transform[15]
        valueSerializer.writeNumber(value_transform_15)
    }
    public static read(buffer: DeserializerBase): ComponentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const size_result : Size = Size_serializer.read(valueDeserializer)
        const localOffset_result : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const windowOffset_result : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const screenOffset_result : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const translate_result : TranslateResult = TranslateResult_serializer.read(valueDeserializer)
        const scale_result : ScaleResult = ScaleResult_serializer.read(valueDeserializer)
        const rotate_result : RotateResult = RotateResult_serializer.read(valueDeserializer)
        const transform_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value2 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value3 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value4 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value5 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value6 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value7 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value8 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value9 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value10 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value11 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value12 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value13 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value14 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value15 : number = (valueDeserializer.readNumber() as number)
        const transform_result : Matrix4Result = ([transform_buf_value0, transform_buf_value1, transform_buf_value2, transform_buf_value3, transform_buf_value4, transform_buf_value5, transform_buf_value6, transform_buf_value7, transform_buf_value8, transform_buf_value9, transform_buf_value10, transform_buf_value11, transform_buf_value12, transform_buf_value13, transform_buf_value14, transform_buf_value15] as Matrix4Result)
        let value : ComponentInfo = ({size: size_result, localOffset: localOffset_result, windowOffset: windowOffset_result, screenOffset: screenOffset_result, translate: translate_result, scale: scale_result, rotate: rotate_result, transform: transform_result} as ComponentInfo)
        return value
    }
}

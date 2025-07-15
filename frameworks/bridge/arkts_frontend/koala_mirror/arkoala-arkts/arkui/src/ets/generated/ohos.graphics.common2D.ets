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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, KInt, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class common2D_Color_serializer {
    public static write(buffer: SerializerBase, value: common2D.Color): void {
        let valueSerializer : SerializerBase = buffer
        const value_alpha  = value.alpha
        valueSerializer.writeNumber(value_alpha)
        const value_red  = value.red
        valueSerializer.writeNumber(value_red)
        const value_green  = value.green
        valueSerializer.writeNumber(value_green)
        const value_blue  = value.blue
        valueSerializer.writeNumber(value_blue)
    }
    public static read(buffer: DeserializerBase): common2D.Color {
        let valueDeserializer : DeserializerBase = buffer
        const alpha_result : number = (valueDeserializer.readNumber() as number)
        const red_result : number = (valueDeserializer.readNumber() as number)
        const green_result : number = (valueDeserializer.readNumber() as number)
        const blue_result : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Color = ({alpha: alpha_result, red: red_result, green: green_result, blue: blue_result} as common2D.Color)
        return value
    }
}
export class common2D_Point_serializer {
    public static write(buffer: SerializerBase, value: common2D.Point): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
    }
    public static read(buffer: DeserializerBase): common2D.Point {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Point = ({x: x_result, y: y_result} as common2D.Point)
        return value
    }
}
export class common2D_Point3d_serializer {
    public static write(buffer: SerializerBase, value: common2D.Point3d): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
    }
    public static read(buffer: DeserializerBase): common2D.Point3d {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Point3d = ({x: x_result, y: y_result, z: z_result} as common2D.Point3d)
        return value
    }
}
export class common2D_Rect_serializer {
    public static write(buffer: SerializerBase, value: common2D.Rect): void {
        let valueSerializer : SerializerBase = buffer
        const value_left  = value.left
        valueSerializer.writeNumber(value_left)
        const value_top  = value.top
        valueSerializer.writeNumber(value_top)
        const value_right  = value.right
        valueSerializer.writeNumber(value_right)
        const value_bottom  = value.bottom
        valueSerializer.writeNumber(value_bottom)
    }
    public static read(buffer: DeserializerBase): common2D.Rect {
        let valueDeserializer : DeserializerBase = buffer
        const left_result : number = (valueDeserializer.readNumber() as number)
        const top_result : number = (valueDeserializer.readNumber() as number)
        const right_result : number = (valueDeserializer.readNumber() as number)
        const bottom_result : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Rect = ({left: left_result, top: top_result, right: right_result, bottom: bottom_result} as common2D.Rect)
        return value
    }
}
export namespace common2D {
    export interface Color {
        alpha: number;
        red: number;
        green: number;
        blue: number;
    }
    export interface Rect {
        left: number;
        top: number;
        right: number;
        bottom: number;
    }
    export interface Point {
        x: number;
        y: number;
    }
    export interface Point3d extends Point {
        z: number;
    }
}

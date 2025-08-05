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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class common2D_Color_serializer {
    public static write(buffer: SerializerBase, value: common2D.Color): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAlpha  = value.alpha
        valueSerializer.writeNumber(valueHolderForAlpha)
        const valueHolderForRed  = value.red
        valueSerializer.writeNumber(valueHolderForRed)
        const valueHolderForGreen  = value.green
        valueSerializer.writeNumber(valueHolderForGreen)
        const valueHolderForBlue  = value.blue
        valueSerializer.writeNumber(valueHolderForBlue)
    }
    public static read(buffer: DeserializerBase): common2D.Color {
        let valueDeserializer : DeserializerBase = buffer
        const alphaTmpResult : number = (valueDeserializer.readNumber() as number)
        const redTmpResult : number = (valueDeserializer.readNumber() as number)
        const greenTmpResult : number = (valueDeserializer.readNumber() as number)
        const blueTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Color = ({alpha: alphaTmpResult, red: redTmpResult, green: greenTmpResult, blue: blueTmpResult} as common2D.Color)
        return value
    }
}
export class common2D_Point_serializer {
    public static write(buffer: SerializerBase, value: common2D.Point): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): common2D.Point {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Point = ({x: xTmpResult, y: yTmpResult} as common2D.Point)
        return value
    }
}
export class common2D_Point3d_serializer {
    public static write(buffer: SerializerBase, value: common2D.Point3d): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ  = value.z
        valueSerializer.writeNumber(valueHolderForZ)
    }
    public static read(buffer: DeserializerBase): common2D.Point3d {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        const zTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Point3d = ({x: xTmpResult, y: yTmpResult, z: zTmpResult} as common2D.Point3d)
        return value
    }
}
export class common2D_Rect_serializer {
    public static write(buffer: SerializerBase, value: common2D.Rect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left
        valueSerializer.writeNumber(valueHolderForLeft)
        const valueHolderForTop  = value.top
        valueSerializer.writeNumber(valueHolderForTop)
        const valueHolderForRight  = value.right
        valueSerializer.writeNumber(valueHolderForRight)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeNumber(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): common2D.Rect {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpResult : number = (valueDeserializer.readNumber() as number)
        const topTmpResult : number = (valueDeserializer.readNumber() as number)
        const rightTmpResult : number = (valueDeserializer.readNumber() as number)
        const bottomTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : common2D.Rect = ({left: leftTmpResult, top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult} as common2D.Rect)
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
    export interface Point3d extends common2D.Point {
        z: number;
    }
}

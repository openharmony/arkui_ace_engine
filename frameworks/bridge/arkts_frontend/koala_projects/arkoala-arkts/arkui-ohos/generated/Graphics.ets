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

import { Size, ColorMetrics, DrawContext, Frame, LengthMetrics, LengthUnit, ShapeClip, ShapeMask, Vector2, Vector3, Circle, CommandPath, Corners, RoundRect } from "arkui.Graphics"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./CallbackTransformer"
import { extractors } from "#handwritten"
import { common2D_Rect_serializer } from "./framework/ohos.graphics.common2D"
import { default as common2D } from "@ohos.graphics.common2D"
export class Frame_serializer {
    public static write(buffer: SerializerBase, value: Frame): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeFloat64(valueHolderForY)
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): Frame {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : double = valueDeserializer.readFloat64()
        const yTmpResult : double = valueDeserializer.readFloat64()
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        let value : Frame = ({x: xTmpResult, y: yTmpResult, width: widthTmpResult, height: heightTmpResult} as Frame)
        return value
    }
}
export class NodeEdges_F64_serializer {
    public static write(buffer: SerializerBase, value: NodeEdges<double>): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left!
        valueSerializer.writeFloat64(valueHolderForLeft)
        const valueHolderForRight  = value.right!
        valueSerializer.writeFloat64(valueHolderForRight)
        const valueHolderForTop  = value.top!
        valueSerializer.writeFloat64(valueHolderForTop)
        const valueHolderForBottom  = value.bottom!
        valueSerializer.writeFloat64(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): NodeEdges<double> {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpResult : double = valueDeserializer.readFloat64()
        const rightTmpResult : double = valueDeserializer.readFloat64()
        const topTmpResult : double = valueDeserializer.readFloat64()
        const bottomTmpResult : double = valueDeserializer.readFloat64()
        let value : NodeEdges<double> = ({left: leftTmpResult, right: rightTmpResult, top: topTmpResult, bottom: bottomTmpResult} as NodeEdges<double>)
        return value
    }
}
export class NodeEdges_I32_serializer {
    public static write(buffer: SerializerBase, value: NodeEdges<int32>): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left!
        valueSerializer.writeInt32(valueHolderForLeft)
        const valueHolderForRight  = value.right!
        valueSerializer.writeInt32(valueHolderForRight)
        const valueHolderForTop  = value.top!
        valueSerializer.writeInt32(valueHolderForTop)
        const valueHolderForBottom  = value.bottom!
        valueSerializer.writeInt32(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): NodeEdges<int32> {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpResult : int32 = valueDeserializer.readInt32()
        const rightTmpResult : int32 = valueDeserializer.readInt32()
        const topTmpResult : int32 = valueDeserializer.readInt32()
        const bottomTmpResult : int32 = valueDeserializer.readInt32()
        let value : NodeEdges<int32> = ({left: leftTmpResult, right: rightTmpResult, top: topTmpResult, bottom: bottomTmpResult} as NodeEdges<int32>)
        return value
    }
}
export class Size_serializer {
    public static write(buffer: SerializerBase, value: Size): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): Size {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        let value : Size = ({width: widthTmpResult, height: heightTmpResult} as Size)
        return value
    }
}
export class ColorMetrics_serializer {
    public static write(buffer: SerializerBase, value: ColorMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRed_  = value.red
        valueSerializer.writeInt32(valueHolderForRed_)
        const valueHolderForGreen_  = value.green
        valueSerializer.writeInt32(valueHolderForGreen_)
        const valueHolderForBlue_  = value.blue
        valueSerializer.writeInt32(valueHolderForBlue_)
        const valueHolderForAlpha_  = value.alpha
        valueSerializer.writeInt32(valueHolderForAlpha_)
        const valueHolderForResourceId_  = value.getResourceId()
        valueSerializer.writeNumber(valueHolderForResourceId_)
    }
    public static read(buffer: DeserializerBase): ColorMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const red_TmpResult : int32 = valueDeserializer.readInt32()
        const green_TmpResult : int32 = valueDeserializer.readInt32()
        const blue_TmpResult : int32 = valueDeserializer.readInt32()
        const alpha_TmpResult : int32 = valueDeserializer.readInt32()
        const resourceId_TmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ColorMetrics = ({red: red_TmpResult, green: green_TmpResult, blue: blue_TmpResult, alpha: alpha_TmpResult, resourceId: resourceId_TmpResult} as ColorMetrics)
        return value
    }
}
export class Corners_F64_serializer {
    public static write(buffer: SerializerBase, value: Corners<double>): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTopLeft  = value.topLeft
        valueSerializer.writeFloat64(valueHolderForTopLeft)
        const valueHolderForTopRight  = value.topRight
        valueSerializer.writeFloat64(valueHolderForTopRight)
        const valueHolderForBottomLeft  = value.bottomLeft
        valueSerializer.writeFloat64(valueHolderForBottomLeft)
        const valueHolderForBottomRight  = value.bottomRight
        valueSerializer.writeFloat64(valueHolderForBottomRight)
    }
    public static read(buffer: DeserializerBase): Corners<double> {
        let valueDeserializer : DeserializerBase = buffer
        const topLeftTmpResult : double = valueDeserializer.readFloat64()
        const topRightTmpResult : double = valueDeserializer.readFloat64()
        const bottomLeftTmpResult : double = valueDeserializer.readFloat64()
        const bottomRightTmpResult : double = valueDeserializer.readFloat64()
        let value : Corners<double> = ({topLeft: topLeftTmpResult, topRight: topRightTmpResult, bottomLeft: bottomLeftTmpResult, bottomRight: bottomRightTmpResult} as Corners<double>)
        return value
    }
}
export class DrawContext_serializer {
    public static write(buffer: SerializerBase, value: DrawContext): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawContextPtr(value))
    }
    public static read(buffer: DeserializerBase): DrawContext {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawContextPtr(ptr)
    }
}
export class LengthMetrics_serializer {
    public static write(buffer: SerializerBase, value: LengthMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUnit  = value.unit
        valueSerializer.writeInt32(valueHolderForUnit.valueOf())
        const valueHolderForValue  = value.value
        valueSerializer.writeFloat64(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): LengthMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const unitTmpResult : LengthUnit = LengthUnit.fromValue(valueDeserializer.readInt32())
        const valueTmpResult : double = valueDeserializer.readFloat64()
        let value : LengthMetrics = ({unit: unitTmpResult, value: valueTmpResult} as LengthMetrics)
        return value
    }
}
export class Vector2_serializer {
    public static write(buffer: SerializerBase, value: Vector2): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeFloat64(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): Vector2 {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : double = valueDeserializer.readFloat64()
        const yTmpResult : double = valueDeserializer.readFloat64()
        let value : Vector2 = ({x: xTmpResult, y: yTmpResult} as Vector2)
        return value
    }
}
export class Vector3_serializer {
    public static write(buffer: SerializerBase, value: Vector3): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeFloat64(valueHolderForY)
        const valueHolderForZ  = value.z
        valueSerializer.writeFloat64(valueHolderForZ)
    }
    public static read(buffer: DeserializerBase): Vector3 {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : double = valueDeserializer.readFloat64()
        const yTmpResult : double = valueDeserializer.readFloat64()
        const zTmpResult : double = valueDeserializer.readFloat64()
        let value : Vector3 = ({x: xTmpResult, y: yTmpResult, z: zTmpResult} as Vector3)
        return value
    }
}
export class Circle_serializer {
    public static write(buffer: SerializerBase, value: Circle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCenterX  = value.centerX
        valueSerializer.writeFloat64(valueHolderForCenterX)
        const valueHolderForCenterY  = value.centerY
        valueSerializer.writeFloat64(valueHolderForCenterY)
        const valueHolderForRadius  = value.radius
        valueSerializer.writeFloat64(valueHolderForRadius)
    }
    public static read(buffer: DeserializerBase): Circle {
        let valueDeserializer : DeserializerBase = buffer
        const centerXTmpResult : double = valueDeserializer.readFloat64()
        const centerYTmpResult : double = valueDeserializer.readFloat64()
        const radiusTmpResult : double = valueDeserializer.readFloat64()
        let value : Circle = ({centerX: centerXTmpResult, centerY: centerYTmpResult, radius: radiusTmpResult} as Circle)
        return value
    }
}
export class Corners_Arkui_Graphics_Vector2_serializer {
    public static write(buffer: SerializerBase, value: Corners<Vector2>): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTopLeft  = value.topLeft
        Vector2_serializer.write(valueSerializer, valueHolderForTopLeft)
        const valueHolderForTopRight  = value.topRight
        Vector2_serializer.write(valueSerializer, valueHolderForTopRight)
        const valueHolderForBottomLeft  = value.bottomLeft
        Vector2_serializer.write(valueSerializer, valueHolderForBottomLeft)
        const valueHolderForBottomRight  = value.bottomRight
        Vector2_serializer.write(valueSerializer, valueHolderForBottomRight)
    }
    public static read(buffer: DeserializerBase): Corners<Vector2> {
        let valueDeserializer : DeserializerBase = buffer
        const topLeftTmpResult : Vector2 = Vector2_serializer.read(valueDeserializer)
        const topRightTmpResult : Vector2 = Vector2_serializer.read(valueDeserializer)
        const bottomLeftTmpResult : Vector2 = Vector2_serializer.read(valueDeserializer)
        const bottomRightTmpResult : Vector2 = Vector2_serializer.read(valueDeserializer)
        let value : Corners<Vector2> = ({topLeft: topLeftTmpResult, topRight: topRightTmpResult, bottomLeft: bottomLeftTmpResult, bottomRight: bottomRightTmpResult} as Corners<Vector2>)
        return value
    }
}
export class CommandPath_serializer {
    public static write(buffer: SerializerBase, value: CommandPath): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCommands  = value.commands
        valueSerializer.writeString(valueHolderForCommands)
    }
    public static read(buffer: DeserializerBase): CommandPath {
        let valueDeserializer : DeserializerBase = buffer
        const commandsTmpResult : string = (valueDeserializer.readString() as string)
        let value : CommandPath = ({commands: commandsTmpResult} as CommandPath)
        return value
    }
}
export class RoundRect_serializer {
    public static write(buffer: SerializerBase, value: RoundRect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRect  = value.rect
        common2D_Rect_serializer.write(valueSerializer, valueHolderForRect)
        const valueHolderForCorners  = value.corners
        Corners_Arkui_Graphics_Vector2_serializer.write(valueSerializer, valueHolderForCorners)
    }
    public static read(buffer: DeserializerBase): RoundRect {
        let valueDeserializer : DeserializerBase = buffer
        const rectTmpResult : common2D.Rect = common2D_Rect_serializer.read(valueDeserializer)
        const cornersTmpResult : Corners<Vector2> = Corners_Arkui_Graphics_Vector2_serializer.read(valueDeserializer)
        let value : RoundRect = ({rect: rectTmpResult, corners: cornersTmpResult} as RoundRect)
        return value
    }
}
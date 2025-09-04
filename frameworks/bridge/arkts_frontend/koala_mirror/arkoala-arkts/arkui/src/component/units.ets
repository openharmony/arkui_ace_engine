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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./../generated/resource"
import { LengthMetrics, LengthMetricsUnit, ColorMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { Color, BorderStyle, FontWeight, FontStyle, DividerMode } from "./enums"
import { OutlineStyle } from "./common"
export class ColorFilterInternal {
    public static fromPtr(ptr: KPointer): ColorFilter {
        return new ColorFilter(false, ptr)
    }
}
export class ColorFilter implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ColorFilter.getFinalizer())
    }
    constructor(value: Array<number>) {
        this(false, ColorFilter.construct(value))
    }
    static construct(value: Array<number>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((value.length).toInt())
        for (let value_counter_i = 0; value_counter_i < value.length; value_counter_i++) {
            const value_element : number = value[value_counter_i]
            thisSerializer.writeNumber(value_element)
        }
        const retval  = ArkUIGeneratedNativeModule._ColorFilter_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorFilter_getFinalizer()
    }
}
export { Resource } from "./../generated/resource"
export type Length = string | number | Resource;
export type PX = string;
export type VP = string | number;
export type FP = string;
export type LPX = string;
export type Percentage = string;
export type Degree = string;
export type Dimension = string | number | Resource;
export type ResourceStr = string | Resource;
export interface Padding {
    top?: Length;
    right?: Length;
    bottom?: Length;
    left?: Length;
}
export interface LocalizedPadding {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
export type Margin = Padding;
export type EdgeWidth = EdgeWidths;
export interface EdgeWidths {
    top?: Length;
    right?: Length;
    bottom?: Length;
    left?: Length;
}
export interface LocalizedEdgeWidths {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
export interface EdgeOutlineWidths {
    top?: Dimension;
    right?: Dimension;
    bottom?: Dimension;
    left?: Dimension;
}
export interface BorderRadiuses {
    topLeft?: Length;
    topRight?: Length;
    bottomLeft?: Length;
    bottomRight?: Length;
}
export interface LocalizedBorderRadiuses {
    topStart?: LengthMetrics;
    topEnd?: LengthMetrics;
    bottomStart?: LengthMetrics;
    bottomEnd?: LengthMetrics;
}
export interface OutlineRadiuses {
    topLeft?: Dimension;
    topRight?: Dimension;
    bottomLeft?: Dimension;
    bottomRight?: Dimension;
}
export interface EdgeColors {
    top?: ResourceColor;
    right?: ResourceColor;
    bottom?: ResourceColor;
    left?: ResourceColor;
}
export interface LocalizedEdgeColors {
    top?: ResourceColor;
    end?: ResourceColor;
    bottom?: ResourceColor;
    start?: ResourceColor;
}
export type LocalizedMargin = LocalizedPadding;
export interface EdgeStyles {
    top?: BorderStyle;
    right?: BorderStyle;
    bottom?: BorderStyle;
    left?: BorderStyle;
}
export interface EdgeOutlineStyles {
    top?: OutlineStyle;
    right?: OutlineStyle;
    bottom?: OutlineStyle;
    left?: OutlineStyle;
}
export interface Offset {
    dx: Length;
    dy: Length;
}
export type ResourceColor = Color | number | string | Resource;
export interface LengthConstrain {
    minLength: Length;
    maxLength: Length;
}
export type VoidCallback = () => void;
export { LengthMetricsUnit } from "./../generated/arkui.Graphics"
export { LengthMetrics } from "./../generated/arkui.Graphics"
export { ColorMetrics } from "./../generated/arkui.Graphics"
export interface Font {
    size?: Length;
    weight?: FontWeight | number | string;
    family?: string | Resource;
    style?: FontStyle;
}
export interface Area {
    width: Length;
    height: Length;
    position: Position;
    globalPosition: Position;
}
export interface Position {
    x?: Length;
    y?: Length;
}
export interface LocalizedPosition {
    start?: LengthMetrics;
    top?: LengthMetrics;
}
export interface Edges {
    top?: Dimension;
    left?: Dimension;
    bottom?: Dimension;
    right?: Dimension;
}
export interface LocalizedEdges {
    top?: LengthMetrics;
    start?: LengthMetrics;
    bottom?: LengthMetrics;
    end?: LengthMetrics;
}
export interface Bias {
    horizontal?: number;
    vertical?: number;
}
export interface ConstraintSizeOptions {
    minWidth?: Length;
    maxWidth?: Length;
    minHeight?: Length;
    maxHeight?: Length;
}
export interface SizeOptions {
    width?: Length;
    height?: Length;
}
export interface BorderOptions {
    width?: EdgeWidths | Length | LocalizedEdgeWidths;
    color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
    radius?: BorderRadiuses | Length | LocalizedBorderRadiuses;
    style?: EdgeStyles | BorderStyle;
    dashGap?: EdgeWidths | LengthMetrics | LocalizedEdgeWidths;
    dashWidth?: EdgeWidths | LengthMetrics | LocalizedEdgeWidths;
}
export interface OutlineOptions {
    width?: EdgeOutlineWidths | Dimension;
    color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
    radius?: OutlineRadiuses | Dimension;
    style?: EdgeOutlineStyles | OutlineStyle;
}
export interface MarkStyle {
    strokeColor?: ResourceColor;
    size?: Length;
    strokeWidth?: Length;
}
export interface TouchPoint {
    x: Dimension;
    y: Dimension;
}
export interface DirectionalEdgesT {
    start: number;
    end: number;
    top: number;
    bottom: number;
}
export interface DividerStyleOptions {
    strokeWidth?: LengthMetrics;
    color?: ResourceColor;
    startMargin?: LengthMetrics;
    endMargin?: LengthMetrics;
    mode?: DividerMode;
}
export interface ChainWeightOptions {
    horizontal?: number;
    vertical?: number;
}
export interface AccessibilityOptions {
    accessibilityPreferred?: boolean;
}
export class ColorFilter_serializer {
    public static write(buffer: SerializerBase, value: ColorFilter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ColorFilter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ColorFilterInternal.fromPtr(ptr)
    }
}
export class AccessibilityOptions_serializer {
    public static write(buffer: SerializerBase, value: AccessibilityOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_accessibilityPreferred  = value.accessibilityPreferred
        let value_accessibilityPreferred_type : int32 = RuntimeType.UNDEFINED
        value_accessibilityPreferred_type = runtimeType(value_accessibilityPreferred)
        valueSerializer.writeInt8((value_accessibilityPreferred_type).toChar())
        if ((value_accessibilityPreferred_type) != (RuntimeType.UNDEFINED)) {
            const value_accessibilityPreferred_value  = value_accessibilityPreferred!
            valueSerializer.writeBoolean(value_accessibilityPreferred_value)
        }
    }
    public static read(buffer: DeserializerBase): AccessibilityOptions {
        let valueDeserializer : DeserializerBase = buffer
        const accessibilityPreferred_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityPreferred_buf : boolean | undefined
        if ((accessibilityPreferred_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            accessibilityPreferred_buf = valueDeserializer.readBoolean()
        }
        const accessibilityPreferred_result : boolean | undefined = accessibilityPreferred_buf
        let value : AccessibilityOptions = ({accessibilityPreferred: accessibilityPreferred_result} as AccessibilityOptions)
        return value
    }
}
export class Bias_serializer {
    public static write(buffer: SerializerBase, value: Bias): void {
        let valueSerializer : SerializerBase = buffer
        const value_horizontal  = value.horizontal
        let value_horizontal_type : int32 = RuntimeType.UNDEFINED
        value_horizontal_type = runtimeType(value_horizontal)
        valueSerializer.writeInt8((value_horizontal_type).toChar())
        if ((value_horizontal_type) != (RuntimeType.UNDEFINED)) {
            const value_horizontal_value  = value_horizontal!
            valueSerializer.writeNumber(value_horizontal_value)
        }
        const value_vertical  = value.vertical
        let value_vertical_type : int32 = RuntimeType.UNDEFINED
        value_vertical_type = runtimeType(value_vertical)
        valueSerializer.writeInt8((value_vertical_type).toChar())
        if ((value_vertical_type) != (RuntimeType.UNDEFINED)) {
            const value_vertical_value  = value_vertical!
            valueSerializer.writeNumber(value_vertical_value)
        }
    }
    public static read(buffer: DeserializerBase): Bias {
        let valueDeserializer : DeserializerBase = buffer
        const horizontal_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let horizontal_buf : number | undefined
        if ((horizontal_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            horizontal_buf = (valueDeserializer.readNumber() as number)
        }
        const horizontal_result : number | undefined = horizontal_buf
        const vertical_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let vertical_buf : number | undefined
        if ((vertical_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            vertical_buf = (valueDeserializer.readNumber() as number)
        }
        const vertical_result : number | undefined = vertical_buf
        let value : Bias = ({horizontal: horizontal_result, vertical: vertical_result} as Bias)
        return value
    }
}
export class ChainWeightOptions_serializer {
    public static write(buffer: SerializerBase, value: ChainWeightOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_horizontal  = value.horizontal
        let value_horizontal_type : int32 = RuntimeType.UNDEFINED
        value_horizontal_type = runtimeType(value_horizontal)
        valueSerializer.writeInt8((value_horizontal_type).toChar())
        if ((value_horizontal_type) != (RuntimeType.UNDEFINED)) {
            const value_horizontal_value  = value_horizontal!
            valueSerializer.writeNumber(value_horizontal_value)
        }
        const value_vertical  = value.vertical
        let value_vertical_type : int32 = RuntimeType.UNDEFINED
        value_vertical_type = runtimeType(value_vertical)
        valueSerializer.writeInt8((value_vertical_type).toChar())
        if ((value_vertical_type) != (RuntimeType.UNDEFINED)) {
            const value_vertical_value  = value_vertical!
            valueSerializer.writeNumber(value_vertical_value)
        }
    }
    public static read(buffer: DeserializerBase): ChainWeightOptions {
        let valueDeserializer : DeserializerBase = buffer
        const horizontal_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let horizontal_buf : number | undefined
        if ((horizontal_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            horizontal_buf = (valueDeserializer.readNumber() as number)
        }
        const horizontal_result : number | undefined = horizontal_buf
        const vertical_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let vertical_buf : number | undefined
        if ((vertical_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            vertical_buf = (valueDeserializer.readNumber() as number)
        }
        const vertical_result : number | undefined = vertical_buf
        let value : ChainWeightOptions = ({horizontal: horizontal_result, vertical: vertical_result} as ChainWeightOptions)
        return value
    }
}
export class DirectionalEdgesT_serializer {
    public static write(buffer: SerializerBase, value: DirectionalEdgesT): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        valueSerializer.writeNumber(value_start)
        const value_end  = value.end
        valueSerializer.writeNumber(value_end)
        const value_top  = value.top
        valueSerializer.writeNumber(value_top)
        const value_bottom  = value.bottom
        valueSerializer.writeNumber(value_bottom)
    }
    public static read(buffer: DeserializerBase): DirectionalEdgesT {
        let valueDeserializer : DeserializerBase = buffer
        const start_result : number = (valueDeserializer.readNumber() as number)
        const end_result : number = (valueDeserializer.readNumber() as number)
        const top_result : number = (valueDeserializer.readNumber() as number)
        const bottom_result : number = (valueDeserializer.readNumber() as number)
        let value : DirectionalEdgesT = ({start: start_result, end: end_result, top: top_result, bottom: bottom_result} as DirectionalEdgesT)
        return value
    }
}
export class EdgeOutlineStyles_serializer {
    public static write(buffer: SerializerBase, value: EdgeOutlineStyles): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = (value_top as OutlineStyle)
            valueSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_top_value))
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = (value_right as OutlineStyle)
            valueSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_right_value))
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = (value_bottom as OutlineStyle)
            valueSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_bottom_value))
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = (value_left as OutlineStyle)
            valueSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_left_value))
        }
    }
    public static read(buffer: DeserializerBase): EdgeOutlineStyles {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : OutlineStyle | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = TypeChecker.OutlineStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const top_result : OutlineStyle | undefined = top_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : OutlineStyle | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            right_buf = TypeChecker.OutlineStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const right_result : OutlineStyle | undefined = right_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : OutlineStyle | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottom_buf = TypeChecker.OutlineStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const bottom_result : OutlineStyle | undefined = bottom_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : OutlineStyle | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            left_buf = TypeChecker.OutlineStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const left_result : OutlineStyle | undefined = left_buf
        let value : EdgeOutlineStyles = ({top: top_result, right: right_result, bottom: bottom_result, left: left_result} as EdgeOutlineStyles)
        return value
    }
}
export class EdgeStyles_serializer {
    public static write(buffer: SerializerBase, value: EdgeStyles): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = (value_top as BorderStyle)
            valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_top_value))
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = (value_right as BorderStyle)
            valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_right_value))
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = (value_bottom as BorderStyle)
            valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_bottom_value))
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = (value_left as BorderStyle)
            valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_left_value))
        }
    }
    public static read(buffer: DeserializerBase): EdgeStyles {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : BorderStyle | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const top_result : BorderStyle | undefined = top_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : BorderStyle | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            right_buf = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const right_result : BorderStyle | undefined = right_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : BorderStyle | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottom_buf = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const bottom_result : BorderStyle | undefined = bottom_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : BorderStyle | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            left_buf = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const left_result : BorderStyle | undefined = left_buf
        let value : EdgeStyles = ({top: top_result, right: right_result, bottom: bottom_result, left: left_result} as EdgeStyles)
        return value
    }
}
export class DividerStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: DividerStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_strokeWidth  = value.strokeWidth
        let value_strokeWidth_type : int32 = RuntimeType.UNDEFINED
        value_strokeWidth_type = runtimeType(value_strokeWidth)
        valueSerializer.writeInt8((value_strokeWidth_type).toChar())
        if ((value_strokeWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeWidth_value  = value_strokeWidth!
            LengthMetrics_serializer.write(valueSerializer, value_strokeWidth_value)
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_startMargin  = value.startMargin
        let value_startMargin_type : int32 = RuntimeType.UNDEFINED
        value_startMargin_type = runtimeType(value_startMargin)
        valueSerializer.writeInt8((value_startMargin_type).toChar())
        if ((value_startMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_startMargin_value  = value_startMargin!
            LengthMetrics_serializer.write(valueSerializer, value_startMargin_value)
        }
        const value_endMargin  = value.endMargin
        let value_endMargin_type : int32 = RuntimeType.UNDEFINED
        value_endMargin_type = runtimeType(value_endMargin)
        valueSerializer.writeInt8((value_endMargin_type).toChar())
        if ((value_endMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_endMargin_value  = value_endMargin!
            LengthMetrics_serializer.write(valueSerializer, value_endMargin_value)
        }
        const value_mode  = value.mode
        let value_mode_type : int32 = RuntimeType.UNDEFINED
        value_mode_type = runtimeType(value_mode)
        valueSerializer.writeInt8((value_mode_type).toChar())
        if ((value_mode_type) != (RuntimeType.UNDEFINED)) {
            const value_mode_value  = (value_mode as DividerMode)
            valueSerializer.writeInt32(TypeChecker.DividerMode_ToNumeric(value_mode_value))
        }
    }
    public static read(buffer: DeserializerBase): DividerStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : LengthMetrics | undefined
        if ((strokeWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strokeWidth_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const strokeWidth_result : LengthMetrics | undefined = strokeWidth_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const startMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMargin_buf : LengthMetrics | undefined
        if ((startMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            startMargin_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const startMargin_result : LengthMetrics | undefined = startMargin_buf
        const endMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMargin_buf : LengthMetrics | undefined
        if ((endMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            endMargin_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const endMargin_result : LengthMetrics | undefined = endMargin_buf
        const mode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mode_buf : DividerMode | undefined
        if ((mode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            mode_buf = TypeChecker.DividerMode_FromNumeric(valueDeserializer.readInt32())
        }
        const mode_result : DividerMode | undefined = mode_buf
        let value : DividerStyleOptions = ({strokeWidth: strokeWidth_result, color: color_result, startMargin: startMargin_result, endMargin: endMargin_result, mode: mode_result} as DividerStyleOptions)
        return value
    }
}
export class EdgeColors_serializer {
    public static write(buffer: SerializerBase, value: EdgeColors): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (TypeChecker.isColor(value_top_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_top_value_0))
            }
            else if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_1)
            }
            else if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_top_value_2  = value_top_value as string
                valueSerializer.writeString(value_top_value_2)
            }
            else if (RuntimeType.OBJECT == value_top_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_top_value_3  = value_top_value as Resource
                Resource_serializer.write(valueSerializer, value_top_value_3)
            }
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = value_right!
            let value_right_value_type : int32 = RuntimeType.UNDEFINED
            value_right_value_type = runtimeType(value_right_value)
            if (TypeChecker.isColor(value_right_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_right_value_0  = value_right_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_right_value_0))
            }
            else if (RuntimeType.NUMBER == value_right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_right_value_1  = value_right_value as number
                valueSerializer.writeNumber(value_right_value_1)
            }
            else if (RuntimeType.STRING == value_right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_right_value_2  = value_right_value as string
                valueSerializer.writeString(value_right_value_2)
            }
            else if (RuntimeType.OBJECT == value_right_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_right_value_3  = value_right_value as Resource
                Resource_serializer.write(valueSerializer, value_right_value_3)
            }
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            let value_bottom_value_type : int32 = RuntimeType.UNDEFINED
            value_bottom_value_type = runtimeType(value_bottom_value)
            if (TypeChecker.isColor(value_bottom_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottom_value_0  = value_bottom_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_bottom_value_0))
            }
            else if (RuntimeType.NUMBER == value_bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottom_value_1  = value_bottom_value as number
                valueSerializer.writeNumber(value_bottom_value_1)
            }
            else if (RuntimeType.STRING == value_bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottom_value_2  = value_bottom_value as string
                valueSerializer.writeString(value_bottom_value_2)
            }
            else if (RuntimeType.OBJECT == value_bottom_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_bottom_value_3  = value_bottom_value as Resource
                Resource_serializer.write(valueSerializer, value_bottom_value_3)
            }
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            let value_left_value_type : int32 = RuntimeType.UNDEFINED
            value_left_value_type = runtimeType(value_left_value)
            if (TypeChecker.isColor(value_left_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_left_value_0  = value_left_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_left_value_0))
            }
            else if (RuntimeType.NUMBER == value_left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_left_value_1  = value_left_value as number
                valueSerializer.writeNumber(value_left_value_1)
            }
            else if (RuntimeType.STRING == value_left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_left_value_2  = value_left_value as string
                valueSerializer.writeString(value_left_value_2)
            }
            else if (RuntimeType.OBJECT == value_left_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_left_value_3  = value_left_value as Resource
                Resource_serializer.write(valueSerializer, value_left_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): EdgeColors {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : ResourceColor | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : Color | number | string | Resource | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (2).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else if (top_buf__selector == (3).toChar()) {
                top_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as Color | number | string | Resource)
        }
        const top_result : ResourceColor | undefined = top_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : ResourceColor | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const right_buf__selector : int32 = valueDeserializer.readInt8()
            let right_buf_ : Color | number | string | Resource | undefined
            if (right_buf__selector == (0).toChar()) {
                right_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (right_buf__selector == (1).toChar()) {
                right_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (right_buf__selector == (2).toChar()) {
                right_buf_ = (valueDeserializer.readString() as string)
            }
            else if (right_buf__selector == (3).toChar()) {
                right_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for right_buf_ has to be chosen through deserialisation.")
            }
            right_buf = (right_buf_ as Color | number | string | Resource)
        }
        const right_result : ResourceColor | undefined = right_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : ResourceColor | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottom_buf__selector : int32 = valueDeserializer.readInt8()
            let bottom_buf_ : Color | number | string | Resource | undefined
            if (bottom_buf__selector == (0).toChar()) {
                bottom_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (bottom_buf__selector == (1).toChar()) {
                bottom_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottom_buf__selector == (2).toChar()) {
                bottom_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottom_buf__selector == (3).toChar()) {
                bottom_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottom_buf_ has to be chosen through deserialisation.")
            }
            bottom_buf = (bottom_buf_ as Color | number | string | Resource)
        }
        const bottom_result : ResourceColor | undefined = bottom_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : ResourceColor | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const left_buf__selector : int32 = valueDeserializer.readInt8()
            let left_buf_ : Color | number | string | Resource | undefined
            if (left_buf__selector == (0).toChar()) {
                left_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (left_buf__selector == (1).toChar()) {
                left_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (left_buf__selector == (2).toChar()) {
                left_buf_ = (valueDeserializer.readString() as string)
            }
            else if (left_buf__selector == (3).toChar()) {
                left_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for left_buf_ has to be chosen through deserialisation.")
            }
            left_buf = (left_buf_ as Color | number | string | Resource)
        }
        const left_result : ResourceColor | undefined = left_buf
        let value : EdgeColors = ({top: top_result, right: right_result, bottom: bottom_result, left: left_result} as EdgeColors)
        return value
    }
}
export class LengthConstrain_serializer {
    public static write(buffer: SerializerBase, value: LengthConstrain): void {
        let valueSerializer : SerializerBase = buffer
        const value_minLength  = value.minLength
        let value_minLength_type : int32 = RuntimeType.UNDEFINED
        value_minLength_type = runtimeType(value_minLength)
        if (RuntimeType.STRING == value_minLength_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_minLength_0  = value_minLength as string
            valueSerializer.writeString(value_minLength_0)
        }
        else if (RuntimeType.NUMBER == value_minLength_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_minLength_1  = value_minLength as number
            valueSerializer.writeNumber(value_minLength_1)
        }
        else if (RuntimeType.OBJECT == value_minLength_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_minLength_2  = value_minLength as Resource
            Resource_serializer.write(valueSerializer, value_minLength_2)
        }
        const value_maxLength  = value.maxLength
        let value_maxLength_type : int32 = RuntimeType.UNDEFINED
        value_maxLength_type = runtimeType(value_maxLength)
        if (RuntimeType.STRING == value_maxLength_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_maxLength_0  = value_maxLength as string
            valueSerializer.writeString(value_maxLength_0)
        }
        else if (RuntimeType.NUMBER == value_maxLength_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_maxLength_1  = value_maxLength as number
            valueSerializer.writeNumber(value_maxLength_1)
        }
        else if (RuntimeType.OBJECT == value_maxLength_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_maxLength_2  = value_maxLength as Resource
            Resource_serializer.write(valueSerializer, value_maxLength_2)
        }
    }
    public static read(buffer: DeserializerBase): LengthConstrain {
        let valueDeserializer : DeserializerBase = buffer
        const minLength_buf_selector : int32 = valueDeserializer.readInt8()
        let minLength_buf : string | number | Resource | undefined
        if (minLength_buf_selector == (0).toChar()) {
            minLength_buf = (valueDeserializer.readString() as string)
        }
        else if (minLength_buf_selector == (1).toChar()) {
            minLength_buf = (valueDeserializer.readNumber() as number)
        }
        else if (minLength_buf_selector == (2).toChar()) {
            minLength_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for minLength_buf has to be chosen through deserialisation.")
        }
        const minLength_result : Length = (minLength_buf as string | number | Resource)
        const maxLength_buf_selector : int32 = valueDeserializer.readInt8()
        let maxLength_buf : string | number | Resource | undefined
        if (maxLength_buf_selector == (0).toChar()) {
            maxLength_buf = (valueDeserializer.readString() as string)
        }
        else if (maxLength_buf_selector == (1).toChar()) {
            maxLength_buf = (valueDeserializer.readNumber() as number)
        }
        else if (maxLength_buf_selector == (2).toChar()) {
            maxLength_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for maxLength_buf has to be chosen through deserialisation.")
        }
        const maxLength_result : Length = (maxLength_buf as string | number | Resource)
        let value : LengthConstrain = ({minLength: minLength_result, maxLength: maxLength_result} as LengthConstrain)
        return value
    }
}
export class LocalizedBorderRadiuses_serializer {
    public static write(buffer: SerializerBase, value: LocalizedBorderRadiuses): void {
        let valueSerializer : SerializerBase = buffer
        const value_topStart  = value.topStart
        let value_topStart_type : int32 = RuntimeType.UNDEFINED
        value_topStart_type = runtimeType(value_topStart)
        valueSerializer.writeInt8((value_topStart_type).toChar())
        if ((value_topStart_type) != (RuntimeType.UNDEFINED)) {
            const value_topStart_value  = value_topStart!
            LengthMetrics_serializer.write(valueSerializer, value_topStart_value)
        }
        const value_topEnd  = value.topEnd
        let value_topEnd_type : int32 = RuntimeType.UNDEFINED
        value_topEnd_type = runtimeType(value_topEnd)
        valueSerializer.writeInt8((value_topEnd_type).toChar())
        if ((value_topEnd_type) != (RuntimeType.UNDEFINED)) {
            const value_topEnd_value  = value_topEnd!
            LengthMetrics_serializer.write(valueSerializer, value_topEnd_value)
        }
        const value_bottomStart  = value.bottomStart
        let value_bottomStart_type : int32 = RuntimeType.UNDEFINED
        value_bottomStart_type = runtimeType(value_bottomStart)
        valueSerializer.writeInt8((value_bottomStart_type).toChar())
        if ((value_bottomStart_type) != (RuntimeType.UNDEFINED)) {
            const value_bottomStart_value  = value_bottomStart!
            LengthMetrics_serializer.write(valueSerializer, value_bottomStart_value)
        }
        const value_bottomEnd  = value.bottomEnd
        let value_bottomEnd_type : int32 = RuntimeType.UNDEFINED
        value_bottomEnd_type = runtimeType(value_bottomEnd)
        valueSerializer.writeInt8((value_bottomEnd_type).toChar())
        if ((value_bottomEnd_type) != (RuntimeType.UNDEFINED)) {
            const value_bottomEnd_value  = value_bottomEnd!
            LengthMetrics_serializer.write(valueSerializer, value_bottomEnd_value)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedBorderRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topStart_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topStart_buf : LengthMetrics | undefined
        if ((topStart_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            topStart_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const topStart_result : LengthMetrics | undefined = topStart_buf
        const topEnd_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topEnd_buf : LengthMetrics | undefined
        if ((topEnd_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            topEnd_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const topEnd_result : LengthMetrics | undefined = topEnd_buf
        const bottomStart_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomStart_buf : LengthMetrics | undefined
        if ((bottomStart_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottomStart_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const bottomStart_result : LengthMetrics | undefined = bottomStart_buf
        const bottomEnd_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomEnd_buf : LengthMetrics | undefined
        if ((bottomEnd_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottomEnd_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const bottomEnd_result : LengthMetrics | undefined = bottomEnd_buf
        let value : LocalizedBorderRadiuses = ({topStart: topStart_result, topEnd: topEnd_result, bottomStart: bottomStart_result, bottomEnd: bottomEnd_result} as LocalizedBorderRadiuses)
        return value
    }
}
export class LocalizedEdgeColors_serializer {
    public static write(buffer: SerializerBase, value: LocalizedEdgeColors): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (TypeChecker.isColor(value_top_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_top_value_0))
            }
            else if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_1)
            }
            else if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_top_value_2  = value_top_value as string
                valueSerializer.writeString(value_top_value_2)
            }
            else if (RuntimeType.OBJECT == value_top_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_top_value_3  = value_top_value as Resource
                Resource_serializer.write(valueSerializer, value_top_value_3)
            }
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            let value_end_value_type : int32 = RuntimeType.UNDEFINED
            value_end_value_type = runtimeType(value_end_value)
            if (TypeChecker.isColor(value_end_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_end_value_0  = value_end_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_end_value_0))
            }
            else if (RuntimeType.NUMBER == value_end_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_end_value_1  = value_end_value as number
                valueSerializer.writeNumber(value_end_value_1)
            }
            else if (RuntimeType.STRING == value_end_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_end_value_2  = value_end_value as string
                valueSerializer.writeString(value_end_value_2)
            }
            else if (RuntimeType.OBJECT == value_end_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_end_value_3  = value_end_value as Resource
                Resource_serializer.write(valueSerializer, value_end_value_3)
            }
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            let value_bottom_value_type : int32 = RuntimeType.UNDEFINED
            value_bottom_value_type = runtimeType(value_bottom_value)
            if (TypeChecker.isColor(value_bottom_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottom_value_0  = value_bottom_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_bottom_value_0))
            }
            else if (RuntimeType.NUMBER == value_bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottom_value_1  = value_bottom_value as number
                valueSerializer.writeNumber(value_bottom_value_1)
            }
            else if (RuntimeType.STRING == value_bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottom_value_2  = value_bottom_value as string
                valueSerializer.writeString(value_bottom_value_2)
            }
            else if (RuntimeType.OBJECT == value_bottom_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_bottom_value_3  = value_bottom_value as Resource
                Resource_serializer.write(valueSerializer, value_bottom_value_3)
            }
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            let value_start_value_type : int32 = RuntimeType.UNDEFINED
            value_start_value_type = runtimeType(value_start_value)
            if (TypeChecker.isColor(value_start_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_start_value_0  = value_start_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_start_value_0))
            }
            else if (RuntimeType.NUMBER == value_start_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_start_value_1  = value_start_value as number
                valueSerializer.writeNumber(value_start_value_1)
            }
            else if (RuntimeType.STRING == value_start_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_start_value_2  = value_start_value as string
                valueSerializer.writeString(value_start_value_2)
            }
            else if (RuntimeType.OBJECT == value_start_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_start_value_3  = value_start_value as Resource
                Resource_serializer.write(valueSerializer, value_start_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdgeColors {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : ResourceColor | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : Color | number | string | Resource | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (2).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else if (top_buf__selector == (3).toChar()) {
                top_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as Color | number | string | Resource)
        }
        const top_result : ResourceColor | undefined = top_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : ResourceColor | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const end_buf__selector : int32 = valueDeserializer.readInt8()
            let end_buf_ : Color | number | string | Resource | undefined
            if (end_buf__selector == (0).toChar()) {
                end_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (end_buf__selector == (1).toChar()) {
                end_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (end_buf__selector == (2).toChar()) {
                end_buf_ = (valueDeserializer.readString() as string)
            }
            else if (end_buf__selector == (3).toChar()) {
                end_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for end_buf_ has to be chosen through deserialisation.")
            }
            end_buf = (end_buf_ as Color | number | string | Resource)
        }
        const end_result : ResourceColor | undefined = end_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : ResourceColor | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottom_buf__selector : int32 = valueDeserializer.readInt8()
            let bottom_buf_ : Color | number | string | Resource | undefined
            if (bottom_buf__selector == (0).toChar()) {
                bottom_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (bottom_buf__selector == (1).toChar()) {
                bottom_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottom_buf__selector == (2).toChar()) {
                bottom_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottom_buf__selector == (3).toChar()) {
                bottom_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottom_buf_ has to be chosen through deserialisation.")
            }
            bottom_buf = (bottom_buf_ as Color | number | string | Resource)
        }
        const bottom_result : ResourceColor | undefined = bottom_buf
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : ResourceColor | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const start_buf__selector : int32 = valueDeserializer.readInt8()
            let start_buf_ : Color | number | string | Resource | undefined
            if (start_buf__selector == (0).toChar()) {
                start_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (start_buf__selector == (1).toChar()) {
                start_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (start_buf__selector == (2).toChar()) {
                start_buf_ = (valueDeserializer.readString() as string)
            }
            else if (start_buf__selector == (3).toChar()) {
                start_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for start_buf_ has to be chosen through deserialisation.")
            }
            start_buf = (start_buf_ as Color | number | string | Resource)
        }
        const start_result : ResourceColor | undefined = start_buf
        let value : LocalizedEdgeColors = ({top: top_result, end: end_result, bottom: bottom_result, start: start_result} as LocalizedEdgeColors)
        return value
    }
}
export class LocalizedEdges_serializer {
    public static write(buffer: SerializerBase, value: LocalizedEdges): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            LengthMetrics_serializer.write(valueSerializer, value_top_value)
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            LengthMetrics_serializer.write(valueSerializer, value_start_value)
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            LengthMetrics_serializer.write(valueSerializer, value_bottom_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            LengthMetrics_serializer.write(valueSerializer, value_end_value)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdges {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : LengthMetrics | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const top_result : LengthMetrics | undefined = top_buf
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : LengthMetrics | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const start_result : LengthMetrics | undefined = start_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : LengthMetrics | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottom_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const bottom_result : LengthMetrics | undefined = bottom_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : LengthMetrics | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const end_result : LengthMetrics | undefined = end_buf
        let value : LocalizedEdges = ({top: top_result, start: start_result, bottom: bottom_result, end: end_result} as LocalizedEdges)
        return value
    }
}
export class LocalizedEdgeWidths_serializer {
    public static write(buffer: SerializerBase, value: LocalizedEdgeWidths): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            LengthMetrics_serializer.write(valueSerializer, value_top_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            LengthMetrics_serializer.write(valueSerializer, value_end_value)
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            LengthMetrics_serializer.write(valueSerializer, value_bottom_value)
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            LengthMetrics_serializer.write(valueSerializer, value_start_value)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdgeWidths {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : LengthMetrics | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const top_result : LengthMetrics | undefined = top_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : LengthMetrics | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const end_result : LengthMetrics | undefined = end_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : LengthMetrics | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottom_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const bottom_result : LengthMetrics | undefined = bottom_buf
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : LengthMetrics | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const start_result : LengthMetrics | undefined = start_buf
        let value : LocalizedEdgeWidths = ({top: top_result, end: end_result, bottom: bottom_result, start: start_result} as LocalizedEdgeWidths)
        return value
    }
}
export class LocalizedPadding_serializer {
    public static write(buffer: SerializerBase, value: LocalizedPadding): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            LengthMetrics_serializer.write(valueSerializer, value_top_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            LengthMetrics_serializer.write(valueSerializer, value_end_value)
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            LengthMetrics_serializer.write(valueSerializer, value_bottom_value)
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            LengthMetrics_serializer.write(valueSerializer, value_start_value)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedPadding {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : LengthMetrics | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const top_result : LengthMetrics | undefined = top_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : LengthMetrics | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const end_result : LengthMetrics | undefined = end_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : LengthMetrics | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bottom_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const bottom_result : LengthMetrics | undefined = bottom_buf
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : LengthMetrics | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const start_result : LengthMetrics | undefined = start_buf
        let value : LocalizedPadding = ({top: top_result, end: end_result, bottom: bottom_result, start: start_result} as LocalizedPadding)
        return value
    }
}
export class LocalizedPosition_serializer {
    public static write(buffer: SerializerBase, value: LocalizedPosition): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            LengthMetrics_serializer.write(valueSerializer, value_start_value)
        }
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            LengthMetrics_serializer.write(valueSerializer, value_top_value)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedPosition {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : LengthMetrics | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const start_result : LengthMetrics | undefined = start_buf
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : LengthMetrics | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const top_result : LengthMetrics | undefined = top_buf
        let value : LocalizedPosition = ({start: start_result, top: top_result} as LocalizedPosition)
        return value
    }
}
export class Offset_serializer {
    public static write(buffer: SerializerBase, value: Offset): void {
        let valueSerializer : SerializerBase = buffer
        const value_dx  = value.dx
        let value_dx_type : int32 = RuntimeType.UNDEFINED
        value_dx_type = runtimeType(value_dx)
        if (RuntimeType.STRING == value_dx_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_dx_0  = value_dx as string
            valueSerializer.writeString(value_dx_0)
        }
        else if (RuntimeType.NUMBER == value_dx_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_dx_1  = value_dx as number
            valueSerializer.writeNumber(value_dx_1)
        }
        else if (RuntimeType.OBJECT == value_dx_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_dx_2  = value_dx as Resource
            Resource_serializer.write(valueSerializer, value_dx_2)
        }
        const value_dy  = value.dy
        let value_dy_type : int32 = RuntimeType.UNDEFINED
        value_dy_type = runtimeType(value_dy)
        if (RuntimeType.STRING == value_dy_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_dy_0  = value_dy as string
            valueSerializer.writeString(value_dy_0)
        }
        else if (RuntimeType.NUMBER == value_dy_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_dy_1  = value_dy as number
            valueSerializer.writeNumber(value_dy_1)
        }
        else if (RuntimeType.OBJECT == value_dy_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_dy_2  = value_dy as Resource
            Resource_serializer.write(valueSerializer, value_dy_2)
        }
    }
    public static read(buffer: DeserializerBase): Offset {
        let valueDeserializer : DeserializerBase = buffer
        const dx_buf_selector : int32 = valueDeserializer.readInt8()
        let dx_buf : string | number | Resource | undefined
        if (dx_buf_selector == (0).toChar()) {
            dx_buf = (valueDeserializer.readString() as string)
        }
        else if (dx_buf_selector == (1).toChar()) {
            dx_buf = (valueDeserializer.readNumber() as number)
        }
        else if (dx_buf_selector == (2).toChar()) {
            dx_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for dx_buf has to be chosen through deserialisation.")
        }
        const dx_result : Length = (dx_buf as string | number | Resource)
        const dy_buf_selector : int32 = valueDeserializer.readInt8()
        let dy_buf : string | number | Resource | undefined
        if (dy_buf_selector == (0).toChar()) {
            dy_buf = (valueDeserializer.readString() as string)
        }
        else if (dy_buf_selector == (1).toChar()) {
            dy_buf = (valueDeserializer.readNumber() as number)
        }
        else if (dy_buf_selector == (2).toChar()) {
            dy_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for dy_buf has to be chosen through deserialisation.")
        }
        const dy_result : Length = (dy_buf as string | number | Resource)
        let value : Offset = ({dx: dx_result, dy: dy_result} as Offset)
        return value
    }
}
export class BorderRadiuses_serializer {
    public static write(buffer: SerializerBase, value: BorderRadiuses): void {
        let valueSerializer : SerializerBase = buffer
        const value_topLeft  = value.topLeft
        let value_topLeft_type : int32 = RuntimeType.UNDEFINED
        value_topLeft_type = runtimeType(value_topLeft)
        valueSerializer.writeInt8((value_topLeft_type).toChar())
        if ((value_topLeft_type) != (RuntimeType.UNDEFINED)) {
            const value_topLeft_value  = value_topLeft!
            let value_topLeft_value_type : int32 = RuntimeType.UNDEFINED
            value_topLeft_value_type = runtimeType(value_topLeft_value)
            if (RuntimeType.STRING == value_topLeft_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_topLeft_value_0  = value_topLeft_value as string
                valueSerializer.writeString(value_topLeft_value_0)
            }
            else if (RuntimeType.NUMBER == value_topLeft_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_topLeft_value_1  = value_topLeft_value as number
                valueSerializer.writeNumber(value_topLeft_value_1)
            }
            else if (RuntimeType.OBJECT == value_topLeft_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_topLeft_value_2  = value_topLeft_value as Resource
                Resource_serializer.write(valueSerializer, value_topLeft_value_2)
            }
        }
        const value_topRight  = value.topRight
        let value_topRight_type : int32 = RuntimeType.UNDEFINED
        value_topRight_type = runtimeType(value_topRight)
        valueSerializer.writeInt8((value_topRight_type).toChar())
        if ((value_topRight_type) != (RuntimeType.UNDEFINED)) {
            const value_topRight_value  = value_topRight!
            let value_topRight_value_type : int32 = RuntimeType.UNDEFINED
            value_topRight_value_type = runtimeType(value_topRight_value)
            if (RuntimeType.STRING == value_topRight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_topRight_value_0  = value_topRight_value as string
                valueSerializer.writeString(value_topRight_value_0)
            }
            else if (RuntimeType.NUMBER == value_topRight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_topRight_value_1  = value_topRight_value as number
                valueSerializer.writeNumber(value_topRight_value_1)
            }
            else if (RuntimeType.OBJECT == value_topRight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_topRight_value_2  = value_topRight_value as Resource
                Resource_serializer.write(valueSerializer, value_topRight_value_2)
            }
        }
        const value_bottomLeft  = value.bottomLeft
        let value_bottomLeft_type : int32 = RuntimeType.UNDEFINED
        value_bottomLeft_type = runtimeType(value_bottomLeft)
        valueSerializer.writeInt8((value_bottomLeft_type).toChar())
        if ((value_bottomLeft_type) != (RuntimeType.UNDEFINED)) {
            const value_bottomLeft_value  = value_bottomLeft!
            let value_bottomLeft_value_type : int32 = RuntimeType.UNDEFINED
            value_bottomLeft_value_type = runtimeType(value_bottomLeft_value)
            if (RuntimeType.STRING == value_bottomLeft_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottomLeft_value_0  = value_bottomLeft_value as string
                valueSerializer.writeString(value_bottomLeft_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottomLeft_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottomLeft_value_1  = value_bottomLeft_value as number
                valueSerializer.writeNumber(value_bottomLeft_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottomLeft_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottomLeft_value_2  = value_bottomLeft_value as Resource
                Resource_serializer.write(valueSerializer, value_bottomLeft_value_2)
            }
        }
        const value_bottomRight  = value.bottomRight
        let value_bottomRight_type : int32 = RuntimeType.UNDEFINED
        value_bottomRight_type = runtimeType(value_bottomRight)
        valueSerializer.writeInt8((value_bottomRight_type).toChar())
        if ((value_bottomRight_type) != (RuntimeType.UNDEFINED)) {
            const value_bottomRight_value  = value_bottomRight!
            let value_bottomRight_value_type : int32 = RuntimeType.UNDEFINED
            value_bottomRight_value_type = runtimeType(value_bottomRight_value)
            if (RuntimeType.STRING == value_bottomRight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottomRight_value_0  = value_bottomRight_value as string
                valueSerializer.writeString(value_bottomRight_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottomRight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottomRight_value_1  = value_bottomRight_value as number
                valueSerializer.writeNumber(value_bottomRight_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottomRight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottomRight_value_2  = value_bottomRight_value as Resource
                Resource_serializer.write(valueSerializer, value_bottomRight_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): BorderRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topLeft_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topLeft_buf : Length | undefined
        if ((topLeft_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const topLeft_buf__selector : int32 = valueDeserializer.readInt8()
            let topLeft_buf_ : string | number | Resource | undefined
            if (topLeft_buf__selector == (0).toChar()) {
                topLeft_buf_ = (valueDeserializer.readString() as string)
            }
            else if (topLeft_buf__selector == (1).toChar()) {
                topLeft_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (topLeft_buf__selector == (2).toChar()) {
                topLeft_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for topLeft_buf_ has to be chosen through deserialisation.")
            }
            topLeft_buf = (topLeft_buf_ as string | number | Resource)
        }
        const topLeft_result : Length | undefined = topLeft_buf
        const topRight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topRight_buf : Length | undefined
        if ((topRight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const topRight_buf__selector : int32 = valueDeserializer.readInt8()
            let topRight_buf_ : string | number | Resource | undefined
            if (topRight_buf__selector == (0).toChar()) {
                topRight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (topRight_buf__selector == (1).toChar()) {
                topRight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (topRight_buf__selector == (2).toChar()) {
                topRight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for topRight_buf_ has to be chosen through deserialisation.")
            }
            topRight_buf = (topRight_buf_ as string | number | Resource)
        }
        const topRight_result : Length | undefined = topRight_buf
        const bottomLeft_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomLeft_buf : Length | undefined
        if ((bottomLeft_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottomLeft_buf__selector : int32 = valueDeserializer.readInt8()
            let bottomLeft_buf_ : string | number | Resource | undefined
            if (bottomLeft_buf__selector == (0).toChar()) {
                bottomLeft_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottomLeft_buf__selector == (1).toChar()) {
                bottomLeft_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottomLeft_buf__selector == (2).toChar()) {
                bottomLeft_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottomLeft_buf_ has to be chosen through deserialisation.")
            }
            bottomLeft_buf = (bottomLeft_buf_ as string | number | Resource)
        }
        const bottomLeft_result : Length | undefined = bottomLeft_buf
        const bottomRight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomRight_buf : Length | undefined
        if ((bottomRight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottomRight_buf__selector : int32 = valueDeserializer.readInt8()
            let bottomRight_buf_ : string | number | Resource | undefined
            if (bottomRight_buf__selector == (0).toChar()) {
                bottomRight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottomRight_buf__selector == (1).toChar()) {
                bottomRight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottomRight_buf__selector == (2).toChar()) {
                bottomRight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottomRight_buf_ has to be chosen through deserialisation.")
            }
            bottomRight_buf = (bottomRight_buf_ as string | number | Resource)
        }
        const bottomRight_result : Length | undefined = bottomRight_buf
        let value : BorderRadiuses = ({topLeft: topLeft_result, topRight: topRight_result, bottomLeft: bottomLeft_result, bottomRight: bottomRight_result} as BorderRadiuses)
        return value
    }
}
export class ConstraintSizeOptions_serializer {
    public static write(buffer: SerializerBase, value: ConstraintSizeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_minWidth  = value.minWidth
        let value_minWidth_type : int32 = RuntimeType.UNDEFINED
        value_minWidth_type = runtimeType(value_minWidth)
        valueSerializer.writeInt8((value_minWidth_type).toChar())
        if ((value_minWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_minWidth_value  = value_minWidth!
            let value_minWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_minWidth_value_type = runtimeType(value_minWidth_value)
            if (RuntimeType.STRING == value_minWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_minWidth_value_0  = value_minWidth_value as string
                valueSerializer.writeString(value_minWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value_minWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_minWidth_value_1  = value_minWidth_value as number
                valueSerializer.writeNumber(value_minWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_minWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_minWidth_value_2  = value_minWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_minWidth_value_2)
            }
        }
        const value_maxWidth  = value.maxWidth
        let value_maxWidth_type : int32 = RuntimeType.UNDEFINED
        value_maxWidth_type = runtimeType(value_maxWidth)
        valueSerializer.writeInt8((value_maxWidth_type).toChar())
        if ((value_maxWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_maxWidth_value  = value_maxWidth!
            let value_maxWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_maxWidth_value_type = runtimeType(value_maxWidth_value)
            if (RuntimeType.STRING == value_maxWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_maxWidth_value_0  = value_maxWidth_value as string
                valueSerializer.writeString(value_maxWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value_maxWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_maxWidth_value_1  = value_maxWidth_value as number
                valueSerializer.writeNumber(value_maxWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_maxWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_maxWidth_value_2  = value_maxWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_maxWidth_value_2)
            }
        }
        const value_minHeight  = value.minHeight
        let value_minHeight_type : int32 = RuntimeType.UNDEFINED
        value_minHeight_type = runtimeType(value_minHeight)
        valueSerializer.writeInt8((value_minHeight_type).toChar())
        if ((value_minHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_minHeight_value  = value_minHeight!
            let value_minHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_minHeight_value_type = runtimeType(value_minHeight_value)
            if (RuntimeType.STRING == value_minHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_minHeight_value_0  = value_minHeight_value as string
                valueSerializer.writeString(value_minHeight_value_0)
            }
            else if (RuntimeType.NUMBER == value_minHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_minHeight_value_1  = value_minHeight_value as number
                valueSerializer.writeNumber(value_minHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value_minHeight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_minHeight_value_2  = value_minHeight_value as Resource
                Resource_serializer.write(valueSerializer, value_minHeight_value_2)
            }
        }
        const value_maxHeight  = value.maxHeight
        let value_maxHeight_type : int32 = RuntimeType.UNDEFINED
        value_maxHeight_type = runtimeType(value_maxHeight)
        valueSerializer.writeInt8((value_maxHeight_type).toChar())
        if ((value_maxHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_maxHeight_value  = value_maxHeight!
            let value_maxHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_maxHeight_value_type = runtimeType(value_maxHeight_value)
            if (RuntimeType.STRING == value_maxHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_maxHeight_value_0  = value_maxHeight_value as string
                valueSerializer.writeString(value_maxHeight_value_0)
            }
            else if (RuntimeType.NUMBER == value_maxHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_maxHeight_value_1  = value_maxHeight_value as number
                valueSerializer.writeNumber(value_maxHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value_maxHeight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_maxHeight_value_2  = value_maxHeight_value as Resource
                Resource_serializer.write(valueSerializer, value_maxHeight_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): ConstraintSizeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const minWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minWidth_buf : Length | undefined
        if ((minWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const minWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let minWidth_buf_ : string | number | Resource | undefined
            if (minWidth_buf__selector == (0).toChar()) {
                minWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (minWidth_buf__selector == (1).toChar()) {
                minWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (minWidth_buf__selector == (2).toChar()) {
                minWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for minWidth_buf_ has to be chosen through deserialisation.")
            }
            minWidth_buf = (minWidth_buf_ as string | number | Resource)
        }
        const minWidth_result : Length | undefined = minWidth_buf
        const maxWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxWidth_buf : Length | undefined
        if ((maxWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const maxWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let maxWidth_buf_ : string | number | Resource | undefined
            if (maxWidth_buf__selector == (0).toChar()) {
                maxWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (maxWidth_buf__selector == (1).toChar()) {
                maxWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (maxWidth_buf__selector == (2).toChar()) {
                maxWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for maxWidth_buf_ has to be chosen through deserialisation.")
            }
            maxWidth_buf = (maxWidth_buf_ as string | number | Resource)
        }
        const maxWidth_result : Length | undefined = maxWidth_buf
        const minHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minHeight_buf : Length | undefined
        if ((minHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const minHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let minHeight_buf_ : string | number | Resource | undefined
            if (minHeight_buf__selector == (0).toChar()) {
                minHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (minHeight_buf__selector == (1).toChar()) {
                minHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (minHeight_buf__selector == (2).toChar()) {
                minHeight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for minHeight_buf_ has to be chosen through deserialisation.")
            }
            minHeight_buf = (minHeight_buf_ as string | number | Resource)
        }
        const minHeight_result : Length | undefined = minHeight_buf
        const maxHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxHeight_buf : Length | undefined
        if ((maxHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const maxHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let maxHeight_buf_ : string | number | Resource | undefined
            if (maxHeight_buf__selector == (0).toChar()) {
                maxHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (maxHeight_buf__selector == (1).toChar()) {
                maxHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (maxHeight_buf__selector == (2).toChar()) {
                maxHeight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for maxHeight_buf_ has to be chosen through deserialisation.")
            }
            maxHeight_buf = (maxHeight_buf_ as string | number | Resource)
        }
        const maxHeight_result : Length | undefined = maxHeight_buf
        let value : ConstraintSizeOptions = ({minWidth: minWidth_result, maxWidth: maxWidth_result, minHeight: minHeight_result, maxHeight: maxHeight_result} as ConstraintSizeOptions)
        return value
    }
}
export class EdgeOutlineWidths_serializer {
    public static write(buffer: SerializerBase, value: EdgeOutlineWidths): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as string
                valueSerializer.writeString(value_top_value_0)
            }
            else if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_1)
            }
            else if (RuntimeType.OBJECT == value_top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_top_value_2  = value_top_value as Resource
                Resource_serializer.write(valueSerializer, value_top_value_2)
            }
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = value_right!
            let value_right_value_type : int32 = RuntimeType.UNDEFINED
            value_right_value_type = runtimeType(value_right_value)
            if (RuntimeType.STRING == value_right_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_right_value_0  = value_right_value as string
                valueSerializer.writeString(value_right_value_0)
            }
            else if (RuntimeType.NUMBER == value_right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_right_value_1  = value_right_value as number
                valueSerializer.writeNumber(value_right_value_1)
            }
            else if (RuntimeType.OBJECT == value_right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_right_value_2  = value_right_value as Resource
                Resource_serializer.write(valueSerializer, value_right_value_2)
            }
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            let value_bottom_value_type : int32 = RuntimeType.UNDEFINED
            value_bottom_value_type = runtimeType(value_bottom_value)
            if (RuntimeType.STRING == value_bottom_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottom_value_0  = value_bottom_value as string
                valueSerializer.writeString(value_bottom_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottom_value_1  = value_bottom_value as number
                valueSerializer.writeNumber(value_bottom_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottom_value_2  = value_bottom_value as Resource
                Resource_serializer.write(valueSerializer, value_bottom_value_2)
            }
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            let value_left_value_type : int32 = RuntimeType.UNDEFINED
            value_left_value_type = runtimeType(value_left_value)
            if (RuntimeType.STRING == value_left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_left_value_0  = value_left_value as string
                valueSerializer.writeString(value_left_value_0)
            }
            else if (RuntimeType.NUMBER == value_left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_left_value_1  = value_left_value as number
                valueSerializer.writeNumber(value_left_value_1)
            }
            else if (RuntimeType.OBJECT == value_left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_left_value_2  = value_left_value as Resource
                Resource_serializer.write(valueSerializer, value_left_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): EdgeOutlineWidths {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : Dimension | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : string | number | Resource | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (2).toChar()) {
                top_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as string | number | Resource)
        }
        const top_result : Dimension | undefined = top_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : Dimension | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const right_buf__selector : int32 = valueDeserializer.readInt8()
            let right_buf_ : string | number | Resource | undefined
            if (right_buf__selector == (0).toChar()) {
                right_buf_ = (valueDeserializer.readString() as string)
            }
            else if (right_buf__selector == (1).toChar()) {
                right_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (right_buf__selector == (2).toChar()) {
                right_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for right_buf_ has to be chosen through deserialisation.")
            }
            right_buf = (right_buf_ as string | number | Resource)
        }
        const right_result : Dimension | undefined = right_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : Dimension | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottom_buf__selector : int32 = valueDeserializer.readInt8()
            let bottom_buf_ : string | number | Resource | undefined
            if (bottom_buf__selector == (0).toChar()) {
                bottom_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottom_buf__selector == (1).toChar()) {
                bottom_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottom_buf__selector == (2).toChar()) {
                bottom_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottom_buf_ has to be chosen through deserialisation.")
            }
            bottom_buf = (bottom_buf_ as string | number | Resource)
        }
        const bottom_result : Dimension | undefined = bottom_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : Dimension | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const left_buf__selector : int32 = valueDeserializer.readInt8()
            let left_buf_ : string | number | Resource | undefined
            if (left_buf__selector == (0).toChar()) {
                left_buf_ = (valueDeserializer.readString() as string)
            }
            else if (left_buf__selector == (1).toChar()) {
                left_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (left_buf__selector == (2).toChar()) {
                left_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for left_buf_ has to be chosen through deserialisation.")
            }
            left_buf = (left_buf_ as string | number | Resource)
        }
        const left_result : Dimension | undefined = left_buf
        let value : EdgeOutlineWidths = ({top: top_result, right: right_result, bottom: bottom_result, left: left_result} as EdgeOutlineWidths)
        return value
    }
}
export class Edges_serializer {
    public static write(buffer: SerializerBase, value: Edges): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as string
                valueSerializer.writeString(value_top_value_0)
            }
            else if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_1)
            }
            else if (RuntimeType.OBJECT == value_top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_top_value_2  = value_top_value as Resource
                Resource_serializer.write(valueSerializer, value_top_value_2)
            }
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            let value_left_value_type : int32 = RuntimeType.UNDEFINED
            value_left_value_type = runtimeType(value_left_value)
            if (RuntimeType.STRING == value_left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_left_value_0  = value_left_value as string
                valueSerializer.writeString(value_left_value_0)
            }
            else if (RuntimeType.NUMBER == value_left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_left_value_1  = value_left_value as number
                valueSerializer.writeNumber(value_left_value_1)
            }
            else if (RuntimeType.OBJECT == value_left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_left_value_2  = value_left_value as Resource
                Resource_serializer.write(valueSerializer, value_left_value_2)
            }
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            let value_bottom_value_type : int32 = RuntimeType.UNDEFINED
            value_bottom_value_type = runtimeType(value_bottom_value)
            if (RuntimeType.STRING == value_bottom_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottom_value_0  = value_bottom_value as string
                valueSerializer.writeString(value_bottom_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottom_value_1  = value_bottom_value as number
                valueSerializer.writeNumber(value_bottom_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottom_value_2  = value_bottom_value as Resource
                Resource_serializer.write(valueSerializer, value_bottom_value_2)
            }
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = value_right!
            let value_right_value_type : int32 = RuntimeType.UNDEFINED
            value_right_value_type = runtimeType(value_right_value)
            if (RuntimeType.STRING == value_right_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_right_value_0  = value_right_value as string
                valueSerializer.writeString(value_right_value_0)
            }
            else if (RuntimeType.NUMBER == value_right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_right_value_1  = value_right_value as number
                valueSerializer.writeNumber(value_right_value_1)
            }
            else if (RuntimeType.OBJECT == value_right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_right_value_2  = value_right_value as Resource
                Resource_serializer.write(valueSerializer, value_right_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): Edges {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : Dimension | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : string | number | Resource | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (2).toChar()) {
                top_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as string | number | Resource)
        }
        const top_result : Dimension | undefined = top_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : Dimension | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const left_buf__selector : int32 = valueDeserializer.readInt8()
            let left_buf_ : string | number | Resource | undefined
            if (left_buf__selector == (0).toChar()) {
                left_buf_ = (valueDeserializer.readString() as string)
            }
            else if (left_buf__selector == (1).toChar()) {
                left_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (left_buf__selector == (2).toChar()) {
                left_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for left_buf_ has to be chosen through deserialisation.")
            }
            left_buf = (left_buf_ as string | number | Resource)
        }
        const left_result : Dimension | undefined = left_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : Dimension | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottom_buf__selector : int32 = valueDeserializer.readInt8()
            let bottom_buf_ : string | number | Resource | undefined
            if (bottom_buf__selector == (0).toChar()) {
                bottom_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottom_buf__selector == (1).toChar()) {
                bottom_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottom_buf__selector == (2).toChar()) {
                bottom_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottom_buf_ has to be chosen through deserialisation.")
            }
            bottom_buf = (bottom_buf_ as string | number | Resource)
        }
        const bottom_result : Dimension | undefined = bottom_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : Dimension | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const right_buf__selector : int32 = valueDeserializer.readInt8()
            let right_buf_ : string | number | Resource | undefined
            if (right_buf__selector == (0).toChar()) {
                right_buf_ = (valueDeserializer.readString() as string)
            }
            else if (right_buf__selector == (1).toChar()) {
                right_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (right_buf__selector == (2).toChar()) {
                right_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for right_buf_ has to be chosen through deserialisation.")
            }
            right_buf = (right_buf_ as string | number | Resource)
        }
        const right_result : Dimension | undefined = right_buf
        let value : Edges = ({top: top_result, left: left_result, bottom: bottom_result, right: right_result} as Edges)
        return value
    }
}
export class EdgeWidths_serializer {
    public static write(buffer: SerializerBase, value: EdgeWidths): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as string
                valueSerializer.writeString(value_top_value_0)
            }
            else if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_1)
            }
            else if (RuntimeType.OBJECT == value_top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_top_value_2  = value_top_value as Resource
                Resource_serializer.write(valueSerializer, value_top_value_2)
            }
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = value_right!
            let value_right_value_type : int32 = RuntimeType.UNDEFINED
            value_right_value_type = runtimeType(value_right_value)
            if (RuntimeType.STRING == value_right_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_right_value_0  = value_right_value as string
                valueSerializer.writeString(value_right_value_0)
            }
            else if (RuntimeType.NUMBER == value_right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_right_value_1  = value_right_value as number
                valueSerializer.writeNumber(value_right_value_1)
            }
            else if (RuntimeType.OBJECT == value_right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_right_value_2  = value_right_value as Resource
                Resource_serializer.write(valueSerializer, value_right_value_2)
            }
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            let value_bottom_value_type : int32 = RuntimeType.UNDEFINED
            value_bottom_value_type = runtimeType(value_bottom_value)
            if (RuntimeType.STRING == value_bottom_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottom_value_0  = value_bottom_value as string
                valueSerializer.writeString(value_bottom_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottom_value_1  = value_bottom_value as number
                valueSerializer.writeNumber(value_bottom_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottom_value_2  = value_bottom_value as Resource
                Resource_serializer.write(valueSerializer, value_bottom_value_2)
            }
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            let value_left_value_type : int32 = RuntimeType.UNDEFINED
            value_left_value_type = runtimeType(value_left_value)
            if (RuntimeType.STRING == value_left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_left_value_0  = value_left_value as string
                valueSerializer.writeString(value_left_value_0)
            }
            else if (RuntimeType.NUMBER == value_left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_left_value_1  = value_left_value as number
                valueSerializer.writeNumber(value_left_value_1)
            }
            else if (RuntimeType.OBJECT == value_left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_left_value_2  = value_left_value as Resource
                Resource_serializer.write(valueSerializer, value_left_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): EdgeWidths {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : Length | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : string | number | Resource | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (2).toChar()) {
                top_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as string | number | Resource)
        }
        const top_result : Length | undefined = top_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : Length | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const right_buf__selector : int32 = valueDeserializer.readInt8()
            let right_buf_ : string | number | Resource | undefined
            if (right_buf__selector == (0).toChar()) {
                right_buf_ = (valueDeserializer.readString() as string)
            }
            else if (right_buf__selector == (1).toChar()) {
                right_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (right_buf__selector == (2).toChar()) {
                right_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for right_buf_ has to be chosen through deserialisation.")
            }
            right_buf = (right_buf_ as string | number | Resource)
        }
        const right_result : Length | undefined = right_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : Length | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottom_buf__selector : int32 = valueDeserializer.readInt8()
            let bottom_buf_ : string | number | Resource | undefined
            if (bottom_buf__selector == (0).toChar()) {
                bottom_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottom_buf__selector == (1).toChar()) {
                bottom_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottom_buf__selector == (2).toChar()) {
                bottom_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottom_buf_ has to be chosen through deserialisation.")
            }
            bottom_buf = (bottom_buf_ as string | number | Resource)
        }
        const bottom_result : Length | undefined = bottom_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : Length | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const left_buf__selector : int32 = valueDeserializer.readInt8()
            let left_buf_ : string | number | Resource | undefined
            if (left_buf__selector == (0).toChar()) {
                left_buf_ = (valueDeserializer.readString() as string)
            }
            else if (left_buf__selector == (1).toChar()) {
                left_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (left_buf__selector == (2).toChar()) {
                left_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for left_buf_ has to be chosen through deserialisation.")
            }
            left_buf = (left_buf_ as string | number | Resource)
        }
        const left_result : Length | undefined = left_buf
        let value : EdgeWidths = ({top: top_result, right: right_result, bottom: bottom_result, left: left_result} as EdgeWidths)
        return value
    }
}
export class Font_serializer {
    public static write(buffer: SerializerBase, value: Font): void {
        let valueSerializer : SerializerBase = buffer
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8((value_size_type).toChar())
        if ((value_size_type) != (RuntimeType.UNDEFINED)) {
            const value_size_value  = value_size!
            let value_size_value_type : int32 = RuntimeType.UNDEFINED
            value_size_value_type = runtimeType(value_size_value)
            if (RuntimeType.STRING == value_size_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_size_value_0  = value_size_value as string
                valueSerializer.writeString(value_size_value_0)
            }
            else if (RuntimeType.NUMBER == value_size_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_size_value_1  = value_size_value as number
                valueSerializer.writeNumber(value_size_value_1)
            }
            else if (RuntimeType.OBJECT == value_size_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_size_value_2  = value_size_value as Resource
                Resource_serializer.write(valueSerializer, value_size_value_2)
            }
        }
        const value_weight  = value.weight
        let value_weight_type : int32 = RuntimeType.UNDEFINED
        value_weight_type = runtimeType(value_weight)
        valueSerializer.writeInt8((value_weight_type).toChar())
        if ((value_weight_type) != (RuntimeType.UNDEFINED)) {
            const value_weight_value  = value_weight!
            let value_weight_value_type : int32 = RuntimeType.UNDEFINED
            value_weight_value_type = runtimeType(value_weight_value)
            if (TypeChecker.isFontWeight(value_weight_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_weight_value_0  = value_weight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_weight_value_0))
            }
            else if (RuntimeType.NUMBER == value_weight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_weight_value_1  = value_weight_value as number
                valueSerializer.writeNumber(value_weight_value_1)
            }
            else if (RuntimeType.STRING == value_weight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_weight_value_2  = value_weight_value as string
                valueSerializer.writeString(value_weight_value_2)
            }
        }
        const value_family  = value.family
        let value_family_type : int32 = RuntimeType.UNDEFINED
        value_family_type = runtimeType(value_family)
        valueSerializer.writeInt8((value_family_type).toChar())
        if ((value_family_type) != (RuntimeType.UNDEFINED)) {
            const value_family_value  = value_family!
            let value_family_value_type : int32 = RuntimeType.UNDEFINED
            value_family_value_type = runtimeType(value_family_value)
            if (RuntimeType.STRING == value_family_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_family_value_0  = value_family_value as string
                valueSerializer.writeString(value_family_value_0)
            }
            else if (RuntimeType.OBJECT == value_family_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_family_value_1  = value_family_value as Resource
                Resource_serializer.write(valueSerializer, value_family_value_1)
            }
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as FontStyle)
            valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_style_value))
        }
    }
    public static read(buffer: DeserializerBase): Font {
        let valueDeserializer : DeserializerBase = buffer
        const size_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let size_buf : Length | undefined
        if ((size_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const size_buf__selector : int32 = valueDeserializer.readInt8()
            let size_buf_ : string | number | Resource | undefined
            if (size_buf__selector == (0).toChar()) {
                size_buf_ = (valueDeserializer.readString() as string)
            }
            else if (size_buf__selector == (1).toChar()) {
                size_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (size_buf__selector == (2).toChar()) {
                size_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for size_buf_ has to be chosen through deserialisation.")
            }
            size_buf = (size_buf_ as string | number | Resource)
        }
        const size_result : Length | undefined = size_buf
        const weight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weight_buf : FontWeight | number | string | undefined
        if ((weight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const weight_buf__selector : int32 = valueDeserializer.readInt8()
            let weight_buf_ : FontWeight | number | string | undefined
            if (weight_buf__selector == (0).toChar()) {
                weight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weight_buf__selector == (1).toChar()) {
                weight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weight_buf__selector == (2).toChar()) {
                weight_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for weight_buf_ has to be chosen through deserialisation.")
            }
            weight_buf = (weight_buf_ as FontWeight | number | string)
        }
        const weight_result : FontWeight | number | string | undefined = weight_buf
        const family_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let family_buf : string | Resource | undefined
        if ((family_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const family_buf__selector : int32 = valueDeserializer.readInt8()
            let family_buf_ : string | Resource | undefined
            if (family_buf__selector == (0).toChar()) {
                family_buf_ = (valueDeserializer.readString() as string)
            }
            else if (family_buf__selector == (1).toChar()) {
                family_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for family_buf_ has to be chosen through deserialisation.")
            }
            family_buf = (family_buf_ as string | Resource)
        }
        const family_result : string | Resource | undefined = family_buf
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : FontStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : FontStyle | undefined = style_buf
        let value : Font = ({size: size_result, weight: weight_result, family: family_result, style: style_result} as Font)
        return value
    }
}
export class MarkStyle_serializer {
    public static write(buffer: SerializerBase, value: MarkStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_strokeColor  = value.strokeColor
        let value_strokeColor_type : int32 = RuntimeType.UNDEFINED
        value_strokeColor_type = runtimeType(value_strokeColor)
        valueSerializer.writeInt8((value_strokeColor_type).toChar())
        if ((value_strokeColor_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeColor_value  = value_strokeColor!
            let value_strokeColor_value_type : int32 = RuntimeType.UNDEFINED
            value_strokeColor_value_type = runtimeType(value_strokeColor_value)
            if (TypeChecker.isColor(value_strokeColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_strokeColor_value_0  = value_strokeColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_strokeColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_strokeColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_strokeColor_value_1  = value_strokeColor_value as number
                valueSerializer.writeNumber(value_strokeColor_value_1)
            }
            else if (RuntimeType.STRING == value_strokeColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_strokeColor_value_2  = value_strokeColor_value as string
                valueSerializer.writeString(value_strokeColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_strokeColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_strokeColor_value_3  = value_strokeColor_value as Resource
                Resource_serializer.write(valueSerializer, value_strokeColor_value_3)
            }
        }
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8((value_size_type).toChar())
        if ((value_size_type) != (RuntimeType.UNDEFINED)) {
            const value_size_value  = value_size!
            let value_size_value_type : int32 = RuntimeType.UNDEFINED
            value_size_value_type = runtimeType(value_size_value)
            if (RuntimeType.STRING == value_size_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_size_value_0  = value_size_value as string
                valueSerializer.writeString(value_size_value_0)
            }
            else if (RuntimeType.NUMBER == value_size_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_size_value_1  = value_size_value as number
                valueSerializer.writeNumber(value_size_value_1)
            }
            else if (RuntimeType.OBJECT == value_size_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_size_value_2  = value_size_value as Resource
                Resource_serializer.write(valueSerializer, value_size_value_2)
            }
        }
        const value_strokeWidth  = value.strokeWidth
        let value_strokeWidth_type : int32 = RuntimeType.UNDEFINED
        value_strokeWidth_type = runtimeType(value_strokeWidth)
        valueSerializer.writeInt8((value_strokeWidth_type).toChar())
        if ((value_strokeWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeWidth_value  = value_strokeWidth!
            let value_strokeWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_strokeWidth_value_type = runtimeType(value_strokeWidth_value)
            if (RuntimeType.STRING == value_strokeWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_strokeWidth_value_0  = value_strokeWidth_value as string
                valueSerializer.writeString(value_strokeWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value_strokeWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_strokeWidth_value_1  = value_strokeWidth_value as number
                valueSerializer.writeNumber(value_strokeWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_strokeWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_strokeWidth_value_2  = value_strokeWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_strokeWidth_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): MarkStyle {
        let valueDeserializer : DeserializerBase = buffer
        const strokeColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeColor_buf : ResourceColor | undefined
        if ((strokeColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const strokeColor_buf__selector : int32 = valueDeserializer.readInt8()
            let strokeColor_buf_ : Color | number | string | Resource | undefined
            if (strokeColor_buf__selector == (0).toChar()) {
                strokeColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (strokeColor_buf__selector == (1).toChar()) {
                strokeColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (strokeColor_buf__selector == (2).toChar()) {
                strokeColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (strokeColor_buf__selector == (3).toChar()) {
                strokeColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for strokeColor_buf_ has to be chosen through deserialisation.")
            }
            strokeColor_buf = (strokeColor_buf_ as Color | number | string | Resource)
        }
        const strokeColor_result : ResourceColor | undefined = strokeColor_buf
        const size_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let size_buf : Length | undefined
        if ((size_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const size_buf__selector : int32 = valueDeserializer.readInt8()
            let size_buf_ : string | number | Resource | undefined
            if (size_buf__selector == (0).toChar()) {
                size_buf_ = (valueDeserializer.readString() as string)
            }
            else if (size_buf__selector == (1).toChar()) {
                size_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (size_buf__selector == (2).toChar()) {
                size_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for size_buf_ has to be chosen through deserialisation.")
            }
            size_buf = (size_buf_ as string | number | Resource)
        }
        const size_result : Length | undefined = size_buf
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : Length | undefined
        if ((strokeWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const strokeWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let strokeWidth_buf_ : string | number | Resource | undefined
            if (strokeWidth_buf__selector == (0).toChar()) {
                strokeWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (strokeWidth_buf__selector == (1).toChar()) {
                strokeWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (strokeWidth_buf__selector == (2).toChar()) {
                strokeWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for strokeWidth_buf_ has to be chosen through deserialisation.")
            }
            strokeWidth_buf = (strokeWidth_buf_ as string | number | Resource)
        }
        const strokeWidth_result : Length | undefined = strokeWidth_buf
        let value : MarkStyle = ({strokeColor: strokeColor_result, size: size_result, strokeWidth: strokeWidth_result} as MarkStyle)
        return value
    }
}
export class OutlineRadiuses_serializer {
    public static write(buffer: SerializerBase, value: OutlineRadiuses): void {
        let valueSerializer : SerializerBase = buffer
        const value_topLeft  = value.topLeft
        let value_topLeft_type : int32 = RuntimeType.UNDEFINED
        value_topLeft_type = runtimeType(value_topLeft)
        valueSerializer.writeInt8((value_topLeft_type).toChar())
        if ((value_topLeft_type) != (RuntimeType.UNDEFINED)) {
            const value_topLeft_value  = value_topLeft!
            let value_topLeft_value_type : int32 = RuntimeType.UNDEFINED
            value_topLeft_value_type = runtimeType(value_topLeft_value)
            if (RuntimeType.STRING == value_topLeft_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_topLeft_value_0  = value_topLeft_value as string
                valueSerializer.writeString(value_topLeft_value_0)
            }
            else if (RuntimeType.NUMBER == value_topLeft_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_topLeft_value_1  = value_topLeft_value as number
                valueSerializer.writeNumber(value_topLeft_value_1)
            }
            else if (RuntimeType.OBJECT == value_topLeft_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_topLeft_value_2  = value_topLeft_value as Resource
                Resource_serializer.write(valueSerializer, value_topLeft_value_2)
            }
        }
        const value_topRight  = value.topRight
        let value_topRight_type : int32 = RuntimeType.UNDEFINED
        value_topRight_type = runtimeType(value_topRight)
        valueSerializer.writeInt8((value_topRight_type).toChar())
        if ((value_topRight_type) != (RuntimeType.UNDEFINED)) {
            const value_topRight_value  = value_topRight!
            let value_topRight_value_type : int32 = RuntimeType.UNDEFINED
            value_topRight_value_type = runtimeType(value_topRight_value)
            if (RuntimeType.STRING == value_topRight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_topRight_value_0  = value_topRight_value as string
                valueSerializer.writeString(value_topRight_value_0)
            }
            else if (RuntimeType.NUMBER == value_topRight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_topRight_value_1  = value_topRight_value as number
                valueSerializer.writeNumber(value_topRight_value_1)
            }
            else if (RuntimeType.OBJECT == value_topRight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_topRight_value_2  = value_topRight_value as Resource
                Resource_serializer.write(valueSerializer, value_topRight_value_2)
            }
        }
        const value_bottomLeft  = value.bottomLeft
        let value_bottomLeft_type : int32 = RuntimeType.UNDEFINED
        value_bottomLeft_type = runtimeType(value_bottomLeft)
        valueSerializer.writeInt8((value_bottomLeft_type).toChar())
        if ((value_bottomLeft_type) != (RuntimeType.UNDEFINED)) {
            const value_bottomLeft_value  = value_bottomLeft!
            let value_bottomLeft_value_type : int32 = RuntimeType.UNDEFINED
            value_bottomLeft_value_type = runtimeType(value_bottomLeft_value)
            if (RuntimeType.STRING == value_bottomLeft_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottomLeft_value_0  = value_bottomLeft_value as string
                valueSerializer.writeString(value_bottomLeft_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottomLeft_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottomLeft_value_1  = value_bottomLeft_value as number
                valueSerializer.writeNumber(value_bottomLeft_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottomLeft_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottomLeft_value_2  = value_bottomLeft_value as Resource
                Resource_serializer.write(valueSerializer, value_bottomLeft_value_2)
            }
        }
        const value_bottomRight  = value.bottomRight
        let value_bottomRight_type : int32 = RuntimeType.UNDEFINED
        value_bottomRight_type = runtimeType(value_bottomRight)
        valueSerializer.writeInt8((value_bottomRight_type).toChar())
        if ((value_bottomRight_type) != (RuntimeType.UNDEFINED)) {
            const value_bottomRight_value  = value_bottomRight!
            let value_bottomRight_value_type : int32 = RuntimeType.UNDEFINED
            value_bottomRight_value_type = runtimeType(value_bottomRight_value)
            if (RuntimeType.STRING == value_bottomRight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottomRight_value_0  = value_bottomRight_value as string
                valueSerializer.writeString(value_bottomRight_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottomRight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottomRight_value_1  = value_bottomRight_value as number
                valueSerializer.writeNumber(value_bottomRight_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottomRight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottomRight_value_2  = value_bottomRight_value as Resource
                Resource_serializer.write(valueSerializer, value_bottomRight_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): OutlineRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topLeft_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topLeft_buf : Dimension | undefined
        if ((topLeft_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const topLeft_buf__selector : int32 = valueDeserializer.readInt8()
            let topLeft_buf_ : string | number | Resource | undefined
            if (topLeft_buf__selector == (0).toChar()) {
                topLeft_buf_ = (valueDeserializer.readString() as string)
            }
            else if (topLeft_buf__selector == (1).toChar()) {
                topLeft_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (topLeft_buf__selector == (2).toChar()) {
                topLeft_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for topLeft_buf_ has to be chosen through deserialisation.")
            }
            topLeft_buf = (topLeft_buf_ as string | number | Resource)
        }
        const topLeft_result : Dimension | undefined = topLeft_buf
        const topRight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topRight_buf : Dimension | undefined
        if ((topRight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const topRight_buf__selector : int32 = valueDeserializer.readInt8()
            let topRight_buf_ : string | number | Resource | undefined
            if (topRight_buf__selector == (0).toChar()) {
                topRight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (topRight_buf__selector == (1).toChar()) {
                topRight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (topRight_buf__selector == (2).toChar()) {
                topRight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for topRight_buf_ has to be chosen through deserialisation.")
            }
            topRight_buf = (topRight_buf_ as string | number | Resource)
        }
        const topRight_result : Dimension | undefined = topRight_buf
        const bottomLeft_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomLeft_buf : Dimension | undefined
        if ((bottomLeft_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottomLeft_buf__selector : int32 = valueDeserializer.readInt8()
            let bottomLeft_buf_ : string | number | Resource | undefined
            if (bottomLeft_buf__selector == (0).toChar()) {
                bottomLeft_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottomLeft_buf__selector == (1).toChar()) {
                bottomLeft_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottomLeft_buf__selector == (2).toChar()) {
                bottomLeft_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottomLeft_buf_ has to be chosen through deserialisation.")
            }
            bottomLeft_buf = (bottomLeft_buf_ as string | number | Resource)
        }
        const bottomLeft_result : Dimension | undefined = bottomLeft_buf
        const bottomRight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomRight_buf : Dimension | undefined
        if ((bottomRight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottomRight_buf__selector : int32 = valueDeserializer.readInt8()
            let bottomRight_buf_ : string | number | Resource | undefined
            if (bottomRight_buf__selector == (0).toChar()) {
                bottomRight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottomRight_buf__selector == (1).toChar()) {
                bottomRight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottomRight_buf__selector == (2).toChar()) {
                bottomRight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottomRight_buf_ has to be chosen through deserialisation.")
            }
            bottomRight_buf = (bottomRight_buf_ as string | number | Resource)
        }
        const bottomRight_result : Dimension | undefined = bottomRight_buf
        let value : OutlineRadiuses = ({topLeft: topLeft_result, topRight: topRight_result, bottomLeft: bottomLeft_result, bottomRight: bottomRight_result} as OutlineRadiuses)
        return value
    }
}
export class Padding_serializer {
    public static write(buffer: SerializerBase, value: Padding): void {
        let valueSerializer : SerializerBase = buffer
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as string
                valueSerializer.writeString(value_top_value_0)
            }
            else if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_1)
            }
            else if (RuntimeType.OBJECT == value_top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_top_value_2  = value_top_value as Resource
                Resource_serializer.write(valueSerializer, value_top_value_2)
            }
        }
        const value_right  = value.right
        let value_right_type : int32 = RuntimeType.UNDEFINED
        value_right_type = runtimeType(value_right)
        valueSerializer.writeInt8((value_right_type).toChar())
        if ((value_right_type) != (RuntimeType.UNDEFINED)) {
            const value_right_value  = value_right!
            let value_right_value_type : int32 = RuntimeType.UNDEFINED
            value_right_value_type = runtimeType(value_right_value)
            if (RuntimeType.STRING == value_right_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_right_value_0  = value_right_value as string
                valueSerializer.writeString(value_right_value_0)
            }
            else if (RuntimeType.NUMBER == value_right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_right_value_1  = value_right_value as number
                valueSerializer.writeNumber(value_right_value_1)
            }
            else if (RuntimeType.OBJECT == value_right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_right_value_2  = value_right_value as Resource
                Resource_serializer.write(valueSerializer, value_right_value_2)
            }
        }
        const value_bottom  = value.bottom
        let value_bottom_type : int32 = RuntimeType.UNDEFINED
        value_bottom_type = runtimeType(value_bottom)
        valueSerializer.writeInt8((value_bottom_type).toChar())
        if ((value_bottom_type) != (RuntimeType.UNDEFINED)) {
            const value_bottom_value  = value_bottom!
            let value_bottom_value_type : int32 = RuntimeType.UNDEFINED
            value_bottom_value_type = runtimeType(value_bottom_value)
            if (RuntimeType.STRING == value_bottom_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_bottom_value_0  = value_bottom_value as string
                valueSerializer.writeString(value_bottom_value_0)
            }
            else if (RuntimeType.NUMBER == value_bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_bottom_value_1  = value_bottom_value as number
                valueSerializer.writeNumber(value_bottom_value_1)
            }
            else if (RuntimeType.OBJECT == value_bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_bottom_value_2  = value_bottom_value as Resource
                Resource_serializer.write(valueSerializer, value_bottom_value_2)
            }
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            let value_left_value_type : int32 = RuntimeType.UNDEFINED
            value_left_value_type = runtimeType(value_left_value)
            if (RuntimeType.STRING == value_left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_left_value_0  = value_left_value as string
                valueSerializer.writeString(value_left_value_0)
            }
            else if (RuntimeType.NUMBER == value_left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_left_value_1  = value_left_value as number
                valueSerializer.writeNumber(value_left_value_1)
            }
            else if (RuntimeType.OBJECT == value_left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_left_value_2  = value_left_value as Resource
                Resource_serializer.write(valueSerializer, value_left_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): Padding {
        let valueDeserializer : DeserializerBase = buffer
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : Length | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : string | number | Resource | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (2).toChar()) {
                top_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as string | number | Resource)
        }
        const top_result : Length | undefined = top_buf
        const right_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let right_buf : Length | undefined
        if ((right_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const right_buf__selector : int32 = valueDeserializer.readInt8()
            let right_buf_ : string | number | Resource | undefined
            if (right_buf__selector == (0).toChar()) {
                right_buf_ = (valueDeserializer.readString() as string)
            }
            else if (right_buf__selector == (1).toChar()) {
                right_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (right_buf__selector == (2).toChar()) {
                right_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for right_buf_ has to be chosen through deserialisation.")
            }
            right_buf = (right_buf_ as string | number | Resource)
        }
        const right_result : Length | undefined = right_buf
        const bottom_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottom_buf : Length | undefined
        if ((bottom_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const bottom_buf__selector : int32 = valueDeserializer.readInt8()
            let bottom_buf_ : string | number | Resource | undefined
            if (bottom_buf__selector == (0).toChar()) {
                bottom_buf_ = (valueDeserializer.readString() as string)
            }
            else if (bottom_buf__selector == (1).toChar()) {
                bottom_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (bottom_buf__selector == (2).toChar()) {
                bottom_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for bottom_buf_ has to be chosen through deserialisation.")
            }
            bottom_buf = (bottom_buf_ as string | number | Resource)
        }
        const bottom_result : Length | undefined = bottom_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : Length | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const left_buf__selector : int32 = valueDeserializer.readInt8()
            let left_buf_ : string | number | Resource | undefined
            if (left_buf__selector == (0).toChar()) {
                left_buf_ = (valueDeserializer.readString() as string)
            }
            else if (left_buf__selector == (1).toChar()) {
                left_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (left_buf__selector == (2).toChar()) {
                left_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for left_buf_ has to be chosen through deserialisation.")
            }
            left_buf = (left_buf_ as string | number | Resource)
        }
        const left_result : Length | undefined = left_buf
        let value : Padding = ({top: top_result, right: right_result, bottom: bottom_result, left: left_result} as Padding)
        return value
    }
}
export class Position_serializer {
    public static write(buffer: SerializerBase, value: Position): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        let value_x_type : int32 = RuntimeType.UNDEFINED
        value_x_type = runtimeType(value_x)
        valueSerializer.writeInt8((value_x_type).toChar())
        if ((value_x_type) != (RuntimeType.UNDEFINED)) {
            const value_x_value  = value_x!
            let value_x_value_type : int32 = RuntimeType.UNDEFINED
            value_x_value_type = runtimeType(value_x_value)
            if (RuntimeType.STRING == value_x_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_x_value_0  = value_x_value as string
                valueSerializer.writeString(value_x_value_0)
            }
            else if (RuntimeType.NUMBER == value_x_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_x_value_1  = value_x_value as number
                valueSerializer.writeNumber(value_x_value_1)
            }
            else if (RuntimeType.OBJECT == value_x_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_x_value_2  = value_x_value as Resource
                Resource_serializer.write(valueSerializer, value_x_value_2)
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
            if (RuntimeType.STRING == value_y_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_y_value_0  = value_y_value as string
                valueSerializer.writeString(value_y_value_0)
            }
            else if (RuntimeType.NUMBER == value_y_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_y_value_1  = value_y_value as number
                valueSerializer.writeNumber(value_y_value_1)
            }
            else if (RuntimeType.OBJECT == value_y_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_y_value_2  = value_y_value as Resource
                Resource_serializer.write(valueSerializer, value_y_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): Position {
        let valueDeserializer : DeserializerBase = buffer
        const x_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let x_buf : Length | undefined
        if ((x_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const x_buf__selector : int32 = valueDeserializer.readInt8()
            let x_buf_ : string | number | Resource | undefined
            if (x_buf__selector == (0).toChar()) {
                x_buf_ = (valueDeserializer.readString() as string)
            }
            else if (x_buf__selector == (1).toChar()) {
                x_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (x_buf__selector == (2).toChar()) {
                x_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for x_buf_ has to be chosen through deserialisation.")
            }
            x_buf = (x_buf_ as string | number | Resource)
        }
        const x_result : Length | undefined = x_buf
        const y_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let y_buf : Length | undefined
        if ((y_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const y_buf__selector : int32 = valueDeserializer.readInt8()
            let y_buf_ : string | number | Resource | undefined
            if (y_buf__selector == (0).toChar()) {
                y_buf_ = (valueDeserializer.readString() as string)
            }
            else if (y_buf__selector == (1).toChar()) {
                y_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (y_buf__selector == (2).toChar()) {
                y_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for y_buf_ has to be chosen through deserialisation.")
            }
            y_buf = (y_buf_ as string | number | Resource)
        }
        const y_result : Length | undefined = y_buf
        let value : Position = ({x: x_result, y: y_result} as Position)
        return value
    }
}
export class SizeOptions_serializer {
    public static write(buffer: SerializerBase, value: SizeOptions): void {
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
    }
    public static read(buffer: DeserializerBase): SizeOptions {
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
        let value : SizeOptions = ({width: width_result, height: height_result} as SizeOptions)
        return value
    }
}
export class Area_serializer {
    public static write(buffer: SerializerBase, value: Area): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        if (RuntimeType.STRING == value_width_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_width_0  = value_width as string
            valueSerializer.writeString(value_width_0)
        }
        else if (RuntimeType.NUMBER == value_width_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_width_1  = value_width as number
            valueSerializer.writeNumber(value_width_1)
        }
        else if (RuntimeType.OBJECT == value_width_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_width_2  = value_width as Resource
            Resource_serializer.write(valueSerializer, value_width_2)
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        if (RuntimeType.STRING == value_height_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_height_0  = value_height as string
            valueSerializer.writeString(value_height_0)
        }
        else if (RuntimeType.NUMBER == value_height_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_height_1  = value_height as number
            valueSerializer.writeNumber(value_height_1)
        }
        else if (RuntimeType.OBJECT == value_height_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_height_2  = value_height as Resource
            Resource_serializer.write(valueSerializer, value_height_2)
        }
        const value_position  = value.position
        Position_serializer.write(valueSerializer, value_position)
        const value_globalPosition  = value.globalPosition
        Position_serializer.write(valueSerializer, value_globalPosition)
    }
    public static read(buffer: DeserializerBase): Area {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_selector : int32 = valueDeserializer.readInt8()
        let width_buf : string | number | Resource | undefined
        if (width_buf_selector == (0).toChar()) {
            width_buf = (valueDeserializer.readString() as string)
        }
        else if (width_buf_selector == (1).toChar()) {
            width_buf = (valueDeserializer.readNumber() as number)
        }
        else if (width_buf_selector == (2).toChar()) {
            width_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for width_buf has to be chosen through deserialisation.")
        }
        const width_result : Length = (width_buf as string | number | Resource)
        const height_buf_selector : int32 = valueDeserializer.readInt8()
        let height_buf : string | number | Resource | undefined
        if (height_buf_selector == (0).toChar()) {
            height_buf = (valueDeserializer.readString() as string)
        }
        else if (height_buf_selector == (1).toChar()) {
            height_buf = (valueDeserializer.readNumber() as number)
        }
        else if (height_buf_selector == (2).toChar()) {
            height_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for height_buf has to be chosen through deserialisation.")
        }
        const height_result : Length = (height_buf as string | number | Resource)
        const position_result : Position = Position_serializer.read(valueDeserializer)
        const globalPosition_result : Position = Position_serializer.read(valueDeserializer)
        let value : Area = ({width: width_result, height: height_result, position: position_result, globalPosition: globalPosition_result} as Area)
        return value
    }
}
export class BorderOptions_serializer {
    public static write(buffer: SerializerBase, value: BorderOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (TypeChecker.isEdgeWidths(value_width_value, true, false, true, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, value_width_value_0)
            }
            else if ((RuntimeType.STRING == value_width_value_type) || (RuntimeType.NUMBER == value_width_value_type) || (RuntimeType.OBJECT == value_width_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as Length
                let value_width_value_1_type : int32 = RuntimeType.UNDEFINED
                value_width_value_1_type = runtimeType(value_width_value_1)
                if (RuntimeType.STRING == value_width_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_width_value_1_0  = value_width_value_1 as string
                    valueSerializer.writeString(value_width_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_width_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_width_value_1_1  = value_width_value_1 as number
                    valueSerializer.writeNumber(value_width_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_width_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_width_value_1_2  = value_width_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_width_value_1_2)
                }
            }
            else if (TypeChecker.isLocalizedEdgeWidths(value_width_value, true, false, true, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_width_value_2  = value_width_value as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, value_width_value_2)
            }
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isEdgeColors(value_color_value, true, false, true, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as EdgeColors
                EdgeColors_serializer.write(valueSerializer, value_color_value_0)
            }
            else if ((TypeChecker.isColor(value_color_value)) || (RuntimeType.NUMBER == value_color_value_type) || (RuntimeType.STRING == value_color_value_type) || (RuntimeType.OBJECT == value_color_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as ResourceColor
                let value_color_value_1_type : int32 = RuntimeType.UNDEFINED
                value_color_value_1_type = runtimeType(value_color_value_1)
                if (TypeChecker.isColor(value_color_value_1)) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_color_value_1_0  = value_color_value_1 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_1_0))
                }
                else if (RuntimeType.NUMBER == value_color_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_color_value_1_1  = value_color_value_1 as number
                    valueSerializer.writeNumber(value_color_value_1_1)
                }
                else if (RuntimeType.STRING == value_color_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_color_value_1_2  = value_color_value_1 as string
                    valueSerializer.writeString(value_color_value_1_2)
                }
                else if (RuntimeType.OBJECT == value_color_value_1_type) {
                    valueSerializer.writeInt8((3).toChar())
                    const value_color_value_1_3  = value_color_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_color_value_1_3)
                }
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_color_value, true, false, true, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, value_color_value_2)
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
            if (TypeChecker.isBorderRadiuses(value_radius_value, false, false, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_radius_value_0  = value_radius_value as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, value_radius_value_0)
            }
            else if ((RuntimeType.STRING == value_radius_value_type) || (RuntimeType.NUMBER == value_radius_value_type) || (RuntimeType.OBJECT == value_radius_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_radius_value_1  = value_radius_value as Length
                let value_radius_value_1_type : int32 = RuntimeType.UNDEFINED
                value_radius_value_1_type = runtimeType(value_radius_value_1)
                if (RuntimeType.STRING == value_radius_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_radius_value_1_0  = value_radius_value_1 as string
                    valueSerializer.writeString(value_radius_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_radius_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_radius_value_1_1  = value_radius_value_1 as number
                    valueSerializer.writeNumber(value_radius_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_radius_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_radius_value_1_2  = value_radius_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_radius_value_1_2)
                }
            }
            else if (TypeChecker.isLocalizedBorderRadiuses(value_radius_value, false, false, false, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_radius_value_2  = value_radius_value as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, value_radius_value_2)
            }
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = value_style!
            let value_style_value_type : int32 = RuntimeType.UNDEFINED
            value_style_value_type = runtimeType(value_style_value)
            if (RuntimeType.OBJECT == value_style_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_style_value_0  = value_style_value as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, value_style_value_0)
            }
            else if (TypeChecker.isBorderStyle(value_style_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_style_value_1  = value_style_value as BorderStyle
                valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_style_value_1))
            }
        }
        const value_dashGap  = value.dashGap
        let value_dashGap_type : int32 = RuntimeType.UNDEFINED
        value_dashGap_type = runtimeType(value_dashGap)
        valueSerializer.writeInt8((value_dashGap_type).toChar())
        if ((value_dashGap_type) != (RuntimeType.UNDEFINED)) {
            const value_dashGap_value  = value_dashGap!
            let value_dashGap_value_type : int32 = RuntimeType.UNDEFINED
            value_dashGap_value_type = runtimeType(value_dashGap_value)
            if (TypeChecker.isEdgeWidths(value_dashGap_value, true, false, true, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_dashGap_value_0  = value_dashGap_value as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, value_dashGap_value_0)
            }
            else if (TypeChecker.isLengthMetrics(value_dashGap_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_dashGap_value_1  = value_dashGap_value as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, value_dashGap_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeWidths(value_dashGap_value, true, false, true, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_dashGap_value_2  = value_dashGap_value as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, value_dashGap_value_2)
            }
        }
        const value_dashWidth  = value.dashWidth
        let value_dashWidth_type : int32 = RuntimeType.UNDEFINED
        value_dashWidth_type = runtimeType(value_dashWidth)
        valueSerializer.writeInt8((value_dashWidth_type).toChar())
        if ((value_dashWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_dashWidth_value  = value_dashWidth!
            let value_dashWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_dashWidth_value_type = runtimeType(value_dashWidth_value)
            if (TypeChecker.isEdgeWidths(value_dashWidth_value, true, false, true, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_dashWidth_value_0  = value_dashWidth_value as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, value_dashWidth_value_0)
            }
            else if (TypeChecker.isLengthMetrics(value_dashWidth_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_dashWidth_value_1  = value_dashWidth_value as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, value_dashWidth_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeWidths(value_dashWidth_value, true, false, true, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_dashWidth_value_2  = value_dashWidth_value as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, value_dashWidth_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): BorderOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : EdgeWidths | Length | LocalizedEdgeWidths | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : EdgeWidths | Length | LocalizedEdgeWidths | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = EdgeWidths_serializer.read(valueDeserializer)
            }
            else if (width_buf__selector == (1).toChar()) {
                const width_buf__u_selector : int32 = valueDeserializer.readInt8()
                let width_buf__u : string | number | Resource | undefined
                if (width_buf__u_selector == (0).toChar()) {
                    width_buf__u = (valueDeserializer.readString() as string)
                }
                else if (width_buf__u_selector == (1).toChar()) {
                    width_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (width_buf__u_selector == (2).toChar()) {
                    width_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for width_buf__u has to be chosen through deserialisation.")
                }
                width_buf_ = (width_buf__u as string | number | Resource)
            }
            else if (width_buf__selector == (2).toChar()) {
                width_buf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as EdgeWidths | Length | LocalizedEdgeWidths)
        }
        const width_result : EdgeWidths | Length | LocalizedEdgeWidths | undefined = width_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = EdgeColors_serializer.read(valueDeserializer)
            }
            else if (color_buf__selector == (1).toChar()) {
                const color_buf__u_selector : int32 = valueDeserializer.readInt8()
                let color_buf__u : Color | number | string | Resource | undefined
                if (color_buf__u_selector == (0).toChar()) {
                    color_buf__u = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                }
                else if (color_buf__u_selector == (1).toChar()) {
                    color_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (color_buf__u_selector == (2).toChar()) {
                    color_buf__u = (valueDeserializer.readString() as string)
                }
                else if (color_buf__u_selector == (3).toChar()) {
                    color_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for color_buf__u has to be chosen through deserialisation.")
                }
                color_buf_ = (color_buf__u as Color | number | string | Resource)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as EdgeColors | ResourceColor | LocalizedEdgeColors)
        }
        const color_result : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = color_buf
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined
            if (radius_buf__selector == (0).toChar()) {
                radius_buf_ = BorderRadiuses_serializer.read(valueDeserializer)
            }
            else if (radius_buf__selector == (1).toChar()) {
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
            else if (radius_buf__selector == (2).toChar()) {
                radius_buf_ = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as BorderRadiuses | Length | LocalizedBorderRadiuses)
        }
        const radius_result : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined = radius_buf
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : EdgeStyles | BorderStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const style_buf__selector : int32 = valueDeserializer.readInt8()
            let style_buf_ : EdgeStyles | BorderStyle | undefined
            if (style_buf__selector == (0).toChar()) {
                style_buf_ = EdgeStyles_serializer.read(valueDeserializer)
            }
            else if (style_buf__selector == (1).toChar()) {
                style_buf_ = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for style_buf_ has to be chosen through deserialisation.")
            }
            style_buf = (style_buf_ as EdgeStyles | BorderStyle)
        }
        const style_result : EdgeStyles | BorderStyle | undefined = style_buf
        const dashGap_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dashGap_buf : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
        if ((dashGap_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const dashGap_buf__selector : int32 = valueDeserializer.readInt8()
            let dashGap_buf_ : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
            if (dashGap_buf__selector == (0).toChar()) {
                dashGap_buf_ = EdgeWidths_serializer.read(valueDeserializer)
            }
            else if (dashGap_buf__selector == (1).toChar()) {
                dashGap_buf_ = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            else if (dashGap_buf__selector == (2).toChar()) {
                dashGap_buf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for dashGap_buf_ has to be chosen through deserialisation.")
            }
            dashGap_buf = (dashGap_buf_ as EdgeWidths | LengthMetrics | LocalizedEdgeWidths)
        }
        const dashGap_result : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = dashGap_buf
        const dashWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dashWidth_buf : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
        if ((dashWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const dashWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let dashWidth_buf_ : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
            if (dashWidth_buf__selector == (0).toChar()) {
                dashWidth_buf_ = EdgeWidths_serializer.read(valueDeserializer)
            }
            else if (dashWidth_buf__selector == (1).toChar()) {
                dashWidth_buf_ = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            else if (dashWidth_buf__selector == (2).toChar()) {
                dashWidth_buf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for dashWidth_buf_ has to be chosen through deserialisation.")
            }
            dashWidth_buf = (dashWidth_buf_ as EdgeWidths | LengthMetrics | LocalizedEdgeWidths)
        }
        const dashWidth_result : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = dashWidth_buf
        let value : BorderOptions = ({width: width_result, color: color_result, radius: radius_result, style: style_result, dashGap: dashGap_result, dashWidth: dashWidth_result} as BorderOptions)
        return value
    }
}
export class OutlineOptions_serializer {
    public static write(buffer: SerializerBase, value: OutlineOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (TypeChecker.isEdgeOutlineWidths(value_width_value, false, false, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as EdgeOutlineWidths
                EdgeOutlineWidths_serializer.write(valueSerializer, value_width_value_0)
            }
            else if ((RuntimeType.STRING == value_width_value_type) || (RuntimeType.NUMBER == value_width_value_type) || (RuntimeType.OBJECT == value_width_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as Dimension
                let value_width_value_1_type : int32 = RuntimeType.UNDEFINED
                value_width_value_1_type = runtimeType(value_width_value_1)
                if (RuntimeType.STRING == value_width_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_width_value_1_0  = value_width_value_1 as string
                    valueSerializer.writeString(value_width_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_width_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_width_value_1_1  = value_width_value_1 as number
                    valueSerializer.writeNumber(value_width_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_width_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_width_value_1_2  = value_width_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_width_value_1_2)
                }
            }
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isEdgeColors(value_color_value, true, false, true, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as EdgeColors
                EdgeColors_serializer.write(valueSerializer, value_color_value_0)
            }
            else if ((TypeChecker.isColor(value_color_value)) || (RuntimeType.NUMBER == value_color_value_type) || (RuntimeType.STRING == value_color_value_type) || (RuntimeType.OBJECT == value_color_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as ResourceColor
                let value_color_value_1_type : int32 = RuntimeType.UNDEFINED
                value_color_value_1_type = runtimeType(value_color_value_1)
                if (TypeChecker.isColor(value_color_value_1)) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_color_value_1_0  = value_color_value_1 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_1_0))
                }
                else if (RuntimeType.NUMBER == value_color_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_color_value_1_1  = value_color_value_1 as number
                    valueSerializer.writeNumber(value_color_value_1_1)
                }
                else if (RuntimeType.STRING == value_color_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_color_value_1_2  = value_color_value_1 as string
                    valueSerializer.writeString(value_color_value_1_2)
                }
                else if (RuntimeType.OBJECT == value_color_value_1_type) {
                    valueSerializer.writeInt8((3).toChar())
                    const value_color_value_1_3  = value_color_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_color_value_1_3)
                }
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_color_value, true, false, true, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, value_color_value_2)
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
            if (TypeChecker.isOutlineRadiuses(value_radius_value, false, false, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_radius_value_0  = value_radius_value as OutlineRadiuses
                OutlineRadiuses_serializer.write(valueSerializer, value_radius_value_0)
            }
            else if ((RuntimeType.STRING == value_radius_value_type) || (RuntimeType.NUMBER == value_radius_value_type) || (RuntimeType.OBJECT == value_radius_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_radius_value_1  = value_radius_value as Dimension
                let value_radius_value_1_type : int32 = RuntimeType.UNDEFINED
                value_radius_value_1_type = runtimeType(value_radius_value_1)
                if (RuntimeType.STRING == value_radius_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_radius_value_1_0  = value_radius_value_1 as string
                    valueSerializer.writeString(value_radius_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_radius_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_radius_value_1_1  = value_radius_value_1 as number
                    valueSerializer.writeNumber(value_radius_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_radius_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_radius_value_1_2  = value_radius_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_radius_value_1_2)
                }
            }
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = value_style!
            let value_style_value_type : int32 = RuntimeType.UNDEFINED
            value_style_value_type = runtimeType(value_style_value)
            if (RuntimeType.OBJECT == value_style_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_style_value_0  = value_style_value as EdgeOutlineStyles
                EdgeOutlineStyles_serializer.write(valueSerializer, value_style_value_0)
            }
            else if (TypeChecker.isOutlineStyle(value_style_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_style_value_1  = value_style_value as OutlineStyle
                valueSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_style_value_1))
            }
        }
    }
    public static read(buffer: DeserializerBase): OutlineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : EdgeOutlineWidths | Dimension | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : EdgeOutlineWidths | Dimension | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = EdgeOutlineWidths_serializer.read(valueDeserializer)
            }
            else if (width_buf__selector == (1).toChar()) {
                const width_buf__u_selector : int32 = valueDeserializer.readInt8()
                let width_buf__u : string | number | Resource | undefined
                if (width_buf__u_selector == (0).toChar()) {
                    width_buf__u = (valueDeserializer.readString() as string)
                }
                else if (width_buf__u_selector == (1).toChar()) {
                    width_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (width_buf__u_selector == (2).toChar()) {
                    width_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for width_buf__u has to be chosen through deserialisation.")
                }
                width_buf_ = (width_buf__u as string | number | Resource)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as EdgeOutlineWidths | Dimension)
        }
        const width_result : EdgeOutlineWidths | Dimension | undefined = width_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = EdgeColors_serializer.read(valueDeserializer)
            }
            else if (color_buf__selector == (1).toChar()) {
                const color_buf__u_selector : int32 = valueDeserializer.readInt8()
                let color_buf__u : Color | number | string | Resource | undefined
                if (color_buf__u_selector == (0).toChar()) {
                    color_buf__u = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                }
                else if (color_buf__u_selector == (1).toChar()) {
                    color_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (color_buf__u_selector == (2).toChar()) {
                    color_buf__u = (valueDeserializer.readString() as string)
                }
                else if (color_buf__u_selector == (3).toChar()) {
                    color_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for color_buf__u has to be chosen through deserialisation.")
                }
                color_buf_ = (color_buf__u as Color | number | string | Resource)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as EdgeColors | ResourceColor | LocalizedEdgeColors)
        }
        const color_result : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = color_buf
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : OutlineRadiuses | Dimension | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : OutlineRadiuses | Dimension | undefined
            if (radius_buf__selector == (0).toChar()) {
                radius_buf_ = OutlineRadiuses_serializer.read(valueDeserializer)
            }
            else if (radius_buf__selector == (1).toChar()) {
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
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as OutlineRadiuses | Dimension)
        }
        const radius_result : OutlineRadiuses | Dimension | undefined = radius_buf
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : EdgeOutlineStyles | OutlineStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const style_buf__selector : int32 = valueDeserializer.readInt8()
            let style_buf_ : EdgeOutlineStyles | OutlineStyle | undefined
            if (style_buf__selector == (0).toChar()) {
                style_buf_ = EdgeOutlineStyles_serializer.read(valueDeserializer)
            }
            else if (style_buf__selector == (1).toChar()) {
                style_buf_ = TypeChecker.OutlineStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for style_buf_ has to be chosen through deserialisation.")
            }
            style_buf = (style_buf_ as EdgeOutlineStyles | OutlineStyle)
        }
        const style_result : EdgeOutlineStyles | OutlineStyle | undefined = style_buf
        let value : OutlineOptions = ({width: width_result, color: color_result, radius: radius_result, style: style_result} as OutlineOptions)
        return value
    }
}

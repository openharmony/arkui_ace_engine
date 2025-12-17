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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Resource } from "global.resource"
import { extractors } from "#handwritten"
import { LengthMetrics, LengthMetricsUnit, ColorMetrics } from "arkui.Graphics"
import { Color, BorderStyle, FontWeight, FontStyle, DividerMode } from "./enums"
import { OutlineStyle } from "./common"
import { LengthMetrics_serializer } from "./../Graphics"
import { Resource_serializer } from "./../framework/resource"
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
    constructor(value: Array<double>) {
        this(false, ColorFilter.construct(value))
    }
    static construct(value: Array<double>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((value.length).toInt())
        for (let valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
            const valueTmpElement : double = value[valueCounterI]
            thisSerializer.writeFloat64(valueTmpElement)
        }
        const retval  = ArkUIGeneratedNativeModule._ColorFilter_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorFilter_getFinalizer()
    }
}
export { Resource } from "global.resource"
export type Length = string | double | Resource;
export type PX = string;
export type VP = string | double;
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
export type ResourceColor = Color | int32 | string | Resource;
export interface LengthConstrain {
    minLength: Length;
    maxLength: Length;
}
export type VoidCallback = () => void;
export { LengthMetricsUnit } from "arkui.Graphics"
export { LengthMetrics } from "arkui.Graphics"
export { ColorMetrics } from "arkui.Graphics"
export interface Font {
    size?: Length;
    weight?: FontWeight | int32 | string;
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
    horizontal?: double;
    vertical?: double;
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
    showInForeground?: boolean;
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
export interface DirectionalEdgesT<T> {
    start: T;
    end: T;
    top: T;
    bottom: T;
}
export interface DividerStyleOptions {
    strokeWidth?: LengthMetrics;
    color?: ResourceColor;
    startMargin?: LengthMetrics;
    endMargin?: LengthMetrics;
    mode?: DividerMode;
}
export interface ScrollBarMargin {
    start?: LengthMetrics;
    end?: LengthMetrics;
}
export interface ChainWeightOptions {
    horizontal?: double;
    vertical?: double;
}
export interface AccessibilityOptions {
    accessibilityPreferred?: boolean;
}
export interface AccessibilityActionOptions {
    scrollStep?: int32;
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
export class AccessibilityActionOptions_serializer {
    public static write(buffer: SerializerBase, value: AccessibilityActionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScrollStep  = value.scrollStep
        if (valueHolderForScrollStep !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollStepTmpValue  = valueHolderForScrollStep!
            valueSerializer.writeInt32(valueHolderForScrollStepTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AccessibilityActionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scrollStepTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollStepTmpBuf : int32 | undefined = undefined
        if ((scrollStepTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollStepTmpBuf = valueDeserializer.readInt32()
        }
        const scrollStepTmpResult : int32 | undefined = scrollStepTmpBuf
        let value : AccessibilityActionOptions = ({scrollStep: scrollStepTmpResult} as AccessibilityActionOptions)
        return value
    }
}
export class AccessibilityOptions_serializer {
    public static write(buffer: SerializerBase, value: AccessibilityOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAccessibilityPreferred  = value.accessibilityPreferred
        if (valueHolderForAccessibilityPreferred !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityPreferredTmpValue  = valueHolderForAccessibilityPreferred!
            valueSerializer.writeBoolean(valueHolderForAccessibilityPreferredTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AccessibilityOptions {
        let valueDeserializer : DeserializerBase = buffer
        const accessibilityPreferredTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityPreferredTmpBuf : boolean | undefined = undefined
        if ((accessibilityPreferredTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accessibilityPreferredTmpBuf = valueDeserializer.readBoolean()
        }
        const accessibilityPreferredTmpResult : boolean | undefined = accessibilityPreferredTmpBuf
        let value : AccessibilityOptions = ({accessibilityPreferred: accessibilityPreferredTmpResult} as AccessibilityOptions)
        return value
    }
}
export class Bias_serializer {
    public static write(buffer: SerializerBase, value: Bias): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHorizontal  = value.horizontal
        if (valueHolderForHorizontal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHorizontalTmpValue  = valueHolderForHorizontal!
            valueSerializer.writeFloat64(valueHolderForHorizontalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVertical  = value.vertical
        if (valueHolderForVertical !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVerticalTmpValue  = valueHolderForVertical!
            valueSerializer.writeFloat64(valueHolderForVerticalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Bias {
        let valueDeserializer : DeserializerBase = buffer
        const horizontalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let horizontalTmpBuf : double | undefined = undefined
        if ((horizontalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            horizontalTmpBuf = valueDeserializer.readFloat64()
        }
        const horizontalTmpResult : double | undefined = horizontalTmpBuf
        const verticalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let verticalTmpBuf : double | undefined = undefined
        if ((verticalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            verticalTmpBuf = valueDeserializer.readFloat64()
        }
        const verticalTmpResult : double | undefined = verticalTmpBuf
        let value : Bias = ({horizontal: horizontalTmpResult, vertical: verticalTmpResult} as Bias)
        return value
    }
}
export class ChainWeightOptions_serializer {
    public static write(buffer: SerializerBase, value: ChainWeightOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHorizontal  = value.horizontal
        if (valueHolderForHorizontal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHorizontalTmpValue  = valueHolderForHorizontal!
            valueSerializer.writeFloat64(valueHolderForHorizontalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVertical  = value.vertical
        if (valueHolderForVertical !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVerticalTmpValue  = valueHolderForVertical!
            valueSerializer.writeFloat64(valueHolderForVerticalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ChainWeightOptions {
        let valueDeserializer : DeserializerBase = buffer
        const horizontalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let horizontalTmpBuf : double | undefined = undefined
        if ((horizontalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            horizontalTmpBuf = valueDeserializer.readFloat64()
        }
        const horizontalTmpResult : double | undefined = horizontalTmpBuf
        const verticalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let verticalTmpBuf : double | undefined = undefined
        if ((verticalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            verticalTmpBuf = valueDeserializer.readFloat64()
        }
        const verticalTmpResult : double | undefined = verticalTmpBuf
        let value : ChainWeightOptions = ({horizontal: horizontalTmpResult, vertical: verticalTmpResult} as ChainWeightOptions)
        return value
    }
}
export class DirectionalEdgesT_serializer {
    public static write(buffer: SerializerBase, value: DirectionalEdgesT<number>): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        valueSerializer.writeNumber(valueHolderForStart)
        const valueHolderForEnd  = value.end
        valueSerializer.writeNumber(valueHolderForEnd)
        const valueHolderForTop  = value.top
        valueSerializer.writeNumber(valueHolderForTop)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeNumber(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): DirectionalEdgesT<number> {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpResult : number = (valueDeserializer.readNumber() as number)
        const endTmpResult : number = (valueDeserializer.readNumber() as number)
        const topTmpResult : number = (valueDeserializer.readNumber() as number)
        const bottomTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : DirectionalEdgesT<number> = ({start: startTmpResult, end: endTmpResult, top: topTmpResult, bottom: bottomTmpResult} as DirectionalEdgesT<number>)
        return value
    }
}
export class EdgeOutlineStyles_serializer {
    public static write(buffer: SerializerBase, value: EdgeOutlineStyles): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = (valueHolderForTop as OutlineStyle)
            valueSerializer.writeInt32(valueHolderForTopTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = (valueHolderForRight as OutlineStyle)
            valueSerializer.writeInt32(valueHolderForRightTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = (valueHolderForBottom as OutlineStyle)
            valueSerializer.writeInt32(valueHolderForBottomTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = (valueHolderForLeft as OutlineStyle)
            valueSerializer.writeInt32(valueHolderForLeftTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeOutlineStyles {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : OutlineStyle | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const topTmpResult : OutlineStyle | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : OutlineStyle | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            rightTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const rightTmpResult : OutlineStyle | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : OutlineStyle | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const bottomTmpResult : OutlineStyle | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : OutlineStyle | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leftTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const leftTmpResult : OutlineStyle | undefined = leftTmpBuf
        let value : EdgeOutlineStyles = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeOutlineStyles)
        return value
    }
}
export class EdgeStyles_serializer {
    public static write(buffer: SerializerBase, value: EdgeStyles): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = (valueHolderForTop as BorderStyle)
            valueSerializer.writeInt32(valueHolderForTopTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = (valueHolderForRight as BorderStyle)
            valueSerializer.writeInt32(valueHolderForRightTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = (valueHolderForBottom as BorderStyle)
            valueSerializer.writeInt32(valueHolderForBottomTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = (valueHolderForLeft as BorderStyle)
            valueSerializer.writeInt32(valueHolderForLeftTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeStyles {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : BorderStyle | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const topTmpResult : BorderStyle | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : BorderStyle | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            rightTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const rightTmpResult : BorderStyle | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : BorderStyle | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const bottomTmpResult : BorderStyle | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : BorderStyle | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leftTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const leftTmpResult : BorderStyle | undefined = leftTmpBuf
        let value : EdgeStyles = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeStyles)
        return value
    }
}
export class DividerStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: DividerStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStartMargin  = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue  = valueHolderForStartMargin!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStartMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin  = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue  = valueHolderForEndMargin!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForEndMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as DividerMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DividerStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidthTmpBuf : LengthMetrics | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeWidthTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeWidthTmpResult : LengthMetrics | undefined = strokeWidthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = valueDeserializer.readInt32()
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | int32 | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMarginTmpBuf : LengthMetrics | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startMarginTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const startMarginTmpResult : LengthMetrics | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMarginTmpBuf : LengthMetrics | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endMarginTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const endMarginTmpResult : LengthMetrics | undefined = endMarginTmpBuf
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeTmpBuf : DividerMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = DividerMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : DividerMode | undefined = modeTmpBuf
        let value : DividerStyleOptions = ({strokeWidth: strokeWidthTmpResult, color: colorTmpResult, startMargin: startMarginTmpResult, endMargin: endMarginTmpResult, mode: modeTmpResult} as DividerStyleOptions)
        return value
    }
}
export class EdgeColors_serializer {
    public static write(buffer: SerializerBase, value: EdgeColors): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as Color
                valueSerializer.writeInt32(valueHolderForTopTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForTopTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as int32
                valueSerializer.writeInt32(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx2)
            } else if (valueHolderForTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForTopTmpValueForIdx3  = valueHolderForTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            if (valueHolderForRightTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRightTmpValueForIdx0  = valueHolderForRightTmpValue as Color
                valueSerializer.writeInt32(valueHolderForRightTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForRightTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRightTmpValueForIdx1  = valueHolderForRightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForRightTmpValueForIdx1)
            } else if (valueHolderForRightTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as string
                valueSerializer.writeString(valueHolderForRightTmpValueForIdx2)
            } else if (valueHolderForRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForRightTmpValueForIdx3  = valueHolderForRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBottomTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBottomTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomTmpValueForIdx1  = valueHolderForBottomTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBottomTmpValueForIdx1)
            } else if (valueHolderForBottomTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as string
                valueSerializer.writeString(valueHolderForBottomTmpValueForIdx2)
            } else if (valueHolderForBottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBottomTmpValueForIdx3  = valueHolderForBottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as Color
                valueSerializer.writeInt32(valueHolderForLeftTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForLeftTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeftTmpValueForIdx1  = valueHolderForLeftTmpValue as int32
                valueSerializer.writeInt32(valueHolderForLeftTmpValueForIdx1)
            } else if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as string
                valueSerializer.writeString(valueHolderForLeftTmpValueForIdx2)
            } else if (valueHolderForLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForLeftTmpValueForIdx3  = valueHolderForLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeColors {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : ResourceColor | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : Color | int32 | string | Resource | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = valueDeserializer.readInt32()
            } else if (topTmpBuf_UnionSelector == (2).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topTmpBuf_UnionSelector == (3).toChar()) {
                topTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as Color | int32 | string | Resource)
        }
        const topTmpResult : ResourceColor | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : ResourceColor | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBuf_ : Color | int32 | string | Resource | undefined
            if (rightTmpBuf_UnionSelector == (0).toChar()) {
                rightTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (rightTmpBuf_UnionSelector == (1).toChar()) {
                rightTmpBuf_ = valueDeserializer.readInt32()
            } else if (rightTmpBuf_UnionSelector == (2).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (rightTmpBuf_UnionSelector == (3).toChar()) {
                rightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for rightTmpBuf_ has to be chosen through deserialisation.")
            }
            rightTmpBuf = (rightTmpBuf_ as Color | int32 | string | Resource)
        }
        const rightTmpResult : ResourceColor | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : ResourceColor | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBuf_ : Color | int32 | string | Resource | undefined
            if (bottomTmpBuf_UnionSelector == (0).toChar()) {
                bottomTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (bottomTmpBuf_UnionSelector == (1).toChar()) {
                bottomTmpBuf_ = valueDeserializer.readInt32()
            } else if (bottomTmpBuf_UnionSelector == (2).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomTmpBuf_UnionSelector == (3).toChar()) {
                bottomTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomTmpBuf = (bottomTmpBuf_ as Color | int32 | string | Resource)
        }
        const bottomTmpResult : ResourceColor | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : ResourceColor | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : Color | int32 | string | Resource | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = valueDeserializer.readInt32()
            } else if (leftTmpBuf_UnionSelector == (2).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (leftTmpBuf_UnionSelector == (3).toChar()) {
                leftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as Color | int32 | string | Resource)
        }
        const leftTmpResult : ResourceColor | undefined = leftTmpBuf
        let value : EdgeColors = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeColors)
        return value
    }
}
export class LengthConstrain_serializer {
    public static write(buffer: SerializerBase, value: LengthConstrain): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMinLength  = value.minLength
        if (valueHolderForMinLength instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMinLengthForIdx0  = valueHolderForMinLength as string
            valueSerializer.writeString(valueHolderForMinLengthForIdx0)
        } else if (valueHolderForMinLength instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMinLengthForIdx1  = valueHolderForMinLength as double
            valueSerializer.writeFloat64(valueHolderForMinLengthForIdx1)
        } else if (valueHolderForMinLength instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForMinLengthForIdx2  = valueHolderForMinLength as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMinLengthForIdx2)
        }
        const valueHolderForMaxLength  = value.maxLength
        if (valueHolderForMaxLength instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMaxLengthForIdx0  = valueHolderForMaxLength as string
            valueSerializer.writeString(valueHolderForMaxLengthForIdx0)
        } else if (valueHolderForMaxLength instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMaxLengthForIdx1  = valueHolderForMaxLength as double
            valueSerializer.writeFloat64(valueHolderForMaxLengthForIdx1)
        } else if (valueHolderForMaxLength instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForMaxLengthForIdx2  = valueHolderForMaxLength as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMaxLengthForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): LengthConstrain {
        let valueDeserializer : DeserializerBase = buffer
        const minLengthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let minLengthTmpBuf : string | double | Resource | undefined
        if (minLengthTmpBufUnionSelector == (0).toChar()) {
            minLengthTmpBuf = (valueDeserializer.readString() as string)
        } else if (minLengthTmpBufUnionSelector == (1).toChar()) {
            minLengthTmpBuf = valueDeserializer.readFloat64()
        } else if (minLengthTmpBufUnionSelector == (2).toChar()) {
            minLengthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for minLengthTmpBuf has to be chosen through deserialisation.")
        }
        const minLengthTmpResult : Length = (minLengthTmpBuf as string | double | Resource)
        const maxLengthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let maxLengthTmpBuf : string | double | Resource | undefined
        if (maxLengthTmpBufUnionSelector == (0).toChar()) {
            maxLengthTmpBuf = (valueDeserializer.readString() as string)
        } else if (maxLengthTmpBufUnionSelector == (1).toChar()) {
            maxLengthTmpBuf = valueDeserializer.readFloat64()
        } else if (maxLengthTmpBufUnionSelector == (2).toChar()) {
            maxLengthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for maxLengthTmpBuf has to be chosen through deserialisation.")
        }
        const maxLengthTmpResult : Length = (maxLengthTmpBuf as string | double | Resource)
        let value : LengthConstrain = ({minLength: minLengthTmpResult, maxLength: maxLengthTmpResult} as LengthConstrain)
        return value
    }
}
export class LocalizedBorderRadiuses_serializer {
    public static write(buffer: SerializerBase, value: LocalizedBorderRadiuses): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTopStart  = value.topStart
        if (valueHolderForTopStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopStartTmpValue  = valueHolderForTopStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTopEnd  = value.topEnd
        if (valueHolderForTopEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopEndTmpValue  = valueHolderForTopEnd!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomStart  = value.bottomStart
        if (valueHolderForBottomStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomStartTmpValue  = valueHolderForBottomStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomEnd  = value.bottomEnd
        if (valueHolderForBottomEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomEndTmpValue  = valueHolderForBottomEnd!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedBorderRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topStartTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topStartTmpBuf : LengthMetrics | undefined = undefined
        if ((topStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topStartTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topStartTmpResult : LengthMetrics | undefined = topStartTmpBuf
        const topEndTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topEndTmpBuf : LengthMetrics | undefined = undefined
        if ((topEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topEndTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topEndTmpResult : LengthMetrics | undefined = topEndTmpBuf
        const bottomStartTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomStartTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomStartTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomStartTmpResult : LengthMetrics | undefined = bottomStartTmpBuf
        const bottomEndTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomEndTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomEndTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomEndTmpResult : LengthMetrics | undefined = bottomEndTmpBuf
        let value : LocalizedBorderRadiuses = ({topStart: topStartTmpResult, topEnd: topEndTmpResult, bottomStart: bottomStartTmpResult, bottomEnd: bottomEndTmpResult} as LocalizedBorderRadiuses)
        return value
    }
}
export class LocalizedEdgeColors_serializer {
    public static write(buffer: SerializerBase, value: LocalizedEdgeColors): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as Color
                valueSerializer.writeInt32(valueHolderForTopTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForTopTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as int32
                valueSerializer.writeInt32(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx2)
            } else if (valueHolderForTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForTopTmpValueForIdx3  = valueHolderForTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            if (valueHolderForEndTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndTmpValueForIdx0  = valueHolderForEndTmpValue as Color
                valueSerializer.writeInt32(valueHolderForEndTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForEndTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForEndTmpValueForIdx1  = valueHolderForEndTmpValue as int32
                valueSerializer.writeInt32(valueHolderForEndTmpValueForIdx1)
            } else if (valueHolderForEndTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForEndTmpValueForIdx2  = valueHolderForEndTmpValue as string
                valueSerializer.writeString(valueHolderForEndTmpValueForIdx2)
            } else if (valueHolderForEndTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForEndTmpValueForIdx3  = valueHolderForEndTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForEndTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBottomTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBottomTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomTmpValueForIdx1  = valueHolderForBottomTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBottomTmpValueForIdx1)
            } else if (valueHolderForBottomTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as string
                valueSerializer.writeString(valueHolderForBottomTmpValueForIdx2)
            } else if (valueHolderForBottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBottomTmpValueForIdx3  = valueHolderForBottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            if (valueHolderForStartTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartTmpValueForIdx0  = valueHolderForStartTmpValue as Color
                valueSerializer.writeInt32(valueHolderForStartTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForStartTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStartTmpValueForIdx1  = valueHolderForStartTmpValue as int32
                valueSerializer.writeInt32(valueHolderForStartTmpValueForIdx1)
            } else if (valueHolderForStartTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStartTmpValueForIdx2  = valueHolderForStartTmpValue as string
                valueSerializer.writeString(valueHolderForStartTmpValueForIdx2)
            } else if (valueHolderForStartTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForStartTmpValueForIdx3  = valueHolderForStartTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStartTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdgeColors {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : ResourceColor | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : Color | int32 | string | Resource | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = valueDeserializer.readInt32()
            } else if (topTmpBuf_UnionSelector == (2).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topTmpBuf_UnionSelector == (3).toChar()) {
                topTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as Color | int32 | string | Resource)
        }
        const topTmpResult : ResourceColor | undefined = topTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : ResourceColor | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endTmpBuf_ : Color | int32 | string | Resource | undefined
            if (endTmpBuf_UnionSelector == (0).toChar()) {
                endTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (endTmpBuf_UnionSelector == (1).toChar()) {
                endTmpBuf_ = valueDeserializer.readInt32()
            } else if (endTmpBuf_UnionSelector == (2).toChar()) {
                endTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (endTmpBuf_UnionSelector == (3).toChar()) {
                endTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endTmpBuf_ has to be chosen through deserialisation.")
            }
            endTmpBuf = (endTmpBuf_ as Color | int32 | string | Resource)
        }
        const endTmpResult : ResourceColor | undefined = endTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : ResourceColor | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBuf_ : Color | int32 | string | Resource | undefined
            if (bottomTmpBuf_UnionSelector == (0).toChar()) {
                bottomTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (bottomTmpBuf_UnionSelector == (1).toChar()) {
                bottomTmpBuf_ = valueDeserializer.readInt32()
            } else if (bottomTmpBuf_UnionSelector == (2).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomTmpBuf_UnionSelector == (3).toChar()) {
                bottomTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomTmpBuf = (bottomTmpBuf_ as Color | int32 | string | Resource)
        }
        const bottomTmpResult : ResourceColor | undefined = bottomTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : ResourceColor | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startTmpBuf_ : Color | int32 | string | Resource | undefined
            if (startTmpBuf_UnionSelector == (0).toChar()) {
                startTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (startTmpBuf_UnionSelector == (1).toChar()) {
                startTmpBuf_ = valueDeserializer.readInt32()
            } else if (startTmpBuf_UnionSelector == (2).toChar()) {
                startTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (startTmpBuf_UnionSelector == (3).toChar()) {
                startTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startTmpBuf_ has to be chosen through deserialisation.")
            }
            startTmpBuf = (startTmpBuf_ as Color | int32 | string | Resource)
        }
        const startTmpResult : ResourceColor | undefined = startTmpBuf
        let value : LocalizedEdgeColors = ({top: topTmpResult, end: endTmpResult, bottom: bottomTmpResult, start: startTmpResult} as LocalizedEdgeColors)
        return value
    }
}
export class LocalizedEdges_serializer {
    public static write(buffer: SerializerBase, value: LocalizedEdges): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdges {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const startTmpResult : LengthMetrics | undefined = startTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : LengthMetrics | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const endTmpResult : LengthMetrics | undefined = endTmpBuf
        let value : LocalizedEdges = ({top: topTmpResult, start: startTmpResult, bottom: bottomTmpResult, end: endTmpResult} as LocalizedEdges)
        return value
    }
}
export class LocalizedEdgeWidths_serializer {
    public static write(buffer: SerializerBase, value: LocalizedEdgeWidths): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdgeWidths {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : LengthMetrics | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const endTmpResult : LengthMetrics | undefined = endTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const startTmpResult : LengthMetrics | undefined = startTmpBuf
        let value : LocalizedEdgeWidths = ({top: topTmpResult, end: endTmpResult, bottom: bottomTmpResult, start: startTmpResult} as LocalizedEdgeWidths)
        return value
    }
}
export class LocalizedPadding_serializer {
    public static write(buffer: SerializerBase, value: LocalizedPadding): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedPadding {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : LengthMetrics | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const endTmpResult : LengthMetrics | undefined = endTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const startTmpResult : LengthMetrics | undefined = startTmpBuf
        let value : LocalizedPadding = ({top: topTmpResult, end: endTmpResult, bottom: bottomTmpResult, start: startTmpResult} as LocalizedPadding)
        return value
    }
}
export class LocalizedPosition_serializer {
    public static write(buffer: SerializerBase, value: LocalizedPosition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedPosition {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const startTmpResult : LengthMetrics | undefined = startTmpBuf
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        let value : LocalizedPosition = ({start: startTmpResult, top: topTmpResult} as LocalizedPosition)
        return value
    }
}
export class Offset_serializer {
    public static write(buffer: SerializerBase, value: Offset): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForDx  = value.dx
        if (valueHolderForDx instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForDxForIdx0  = valueHolderForDx as string
            valueSerializer.writeString(valueHolderForDxForIdx0)
        } else if (valueHolderForDx instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForDxForIdx1  = valueHolderForDx as double
            valueSerializer.writeFloat64(valueHolderForDxForIdx1)
        } else if (valueHolderForDx instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForDxForIdx2  = valueHolderForDx as Resource
            Resource_serializer.write(valueSerializer, valueHolderForDxForIdx2)
        }
        const valueHolderForDy  = value.dy
        if (valueHolderForDy instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForDyForIdx0  = valueHolderForDy as string
            valueSerializer.writeString(valueHolderForDyForIdx0)
        } else if (valueHolderForDy instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForDyForIdx1  = valueHolderForDy as double
            valueSerializer.writeFloat64(valueHolderForDyForIdx1)
        } else if (valueHolderForDy instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForDyForIdx2  = valueHolderForDy as Resource
            Resource_serializer.write(valueSerializer, valueHolderForDyForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): Offset {
        let valueDeserializer : DeserializerBase = buffer
        const dxTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let dxTmpBuf : string | double | Resource | undefined
        if (dxTmpBufUnionSelector == (0).toChar()) {
            dxTmpBuf = (valueDeserializer.readString() as string)
        } else if (dxTmpBufUnionSelector == (1).toChar()) {
            dxTmpBuf = valueDeserializer.readFloat64()
        } else if (dxTmpBufUnionSelector == (2).toChar()) {
            dxTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for dxTmpBuf has to be chosen through deserialisation.")
        }
        const dxTmpResult : Length = (dxTmpBuf as string | double | Resource)
        const dyTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let dyTmpBuf : string | double | Resource | undefined
        if (dyTmpBufUnionSelector == (0).toChar()) {
            dyTmpBuf = (valueDeserializer.readString() as string)
        } else if (dyTmpBufUnionSelector == (1).toChar()) {
            dyTmpBuf = valueDeserializer.readFloat64()
        } else if (dyTmpBufUnionSelector == (2).toChar()) {
            dyTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for dyTmpBuf has to be chosen through deserialisation.")
        }
        const dyTmpResult : Length = (dyTmpBuf as string | double | Resource)
        let value : Offset = ({dx: dxTmpResult, dy: dyTmpResult} as Offset)
        return value
    }
}
export class BorderRadiuses_serializer {
    public static write(buffer: SerializerBase, value: BorderRadiuses): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTopLeft  = value.topLeft
        if (valueHolderForTopLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopLeftTmpValue  = valueHolderForTopLeft!
            if (valueHolderForTopLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopLeftTmpValueForIdx0  = valueHolderForTopLeftTmpValue as string
                valueSerializer.writeString(valueHolderForTopLeftTmpValueForIdx0)
            } else if (valueHolderForTopLeftTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopLeftTmpValueForIdx1  = valueHolderForTopLeftTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTopLeftTmpValueForIdx1)
            } else if (valueHolderForTopLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopLeftTmpValueForIdx2  = valueHolderForTopLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTopRight  = value.topRight
        if (valueHolderForTopRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopRightTmpValue  = valueHolderForTopRight!
            if (valueHolderForTopRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopRightTmpValueForIdx0  = valueHolderForTopRightTmpValue as string
                valueSerializer.writeString(valueHolderForTopRightTmpValueForIdx0)
            } else if (valueHolderForTopRightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopRightTmpValueForIdx1  = valueHolderForTopRightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTopRightTmpValueForIdx1)
            } else if (valueHolderForTopRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopRightTmpValueForIdx2  = valueHolderForTopRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomLeft  = value.bottomLeft
        if (valueHolderForBottomLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomLeftTmpValue  = valueHolderForBottomLeft!
            if (valueHolderForBottomLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomLeftTmpValueForIdx0  = valueHolderForBottomLeftTmpValue as string
                valueSerializer.writeString(valueHolderForBottomLeftTmpValueForIdx0)
            } else if (valueHolderForBottomLeftTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomLeftTmpValueForIdx1  = valueHolderForBottomLeftTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBottomLeftTmpValueForIdx1)
            } else if (valueHolderForBottomLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomLeftTmpValueForIdx2  = valueHolderForBottomLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomRight  = value.bottomRight
        if (valueHolderForBottomRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomRightTmpValue  = valueHolderForBottomRight!
            if (valueHolderForBottomRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomRightTmpValueForIdx0  = valueHolderForBottomRightTmpValue as string
                valueSerializer.writeString(valueHolderForBottomRightTmpValueForIdx0)
            } else if (valueHolderForBottomRightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomRightTmpValueForIdx1  = valueHolderForBottomRightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBottomRightTmpValueForIdx1)
            } else if (valueHolderForBottomRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomRightTmpValueForIdx2  = valueHolderForBottomRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BorderRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topLeftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topLeftTmpBuf : Length | undefined = undefined
        if ((topLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topLeftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topLeftTmpBuf_ : string | double | Resource | undefined
            if (topLeftTmpBuf_UnionSelector == (0).toChar()) {
                topLeftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topLeftTmpBuf_UnionSelector == (1).toChar()) {
                topLeftTmpBuf_ = valueDeserializer.readFloat64()
            } else if (topLeftTmpBuf_UnionSelector == (2).toChar()) {
                topLeftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topLeftTmpBuf_ has to be chosen through deserialisation.")
            }
            topLeftTmpBuf = (topLeftTmpBuf_ as string | double | Resource)
        }
        const topLeftTmpResult : Length | undefined = topLeftTmpBuf
        const topRightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topRightTmpBuf : Length | undefined = undefined
        if ((topRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topRightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topRightTmpBuf_ : string | double | Resource | undefined
            if (topRightTmpBuf_UnionSelector == (0).toChar()) {
                topRightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topRightTmpBuf_UnionSelector == (1).toChar()) {
                topRightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (topRightTmpBuf_UnionSelector == (2).toChar()) {
                topRightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topRightTmpBuf_ has to be chosen through deserialisation.")
            }
            topRightTmpBuf = (topRightTmpBuf_ as string | double | Resource)
        }
        const topRightTmpResult : Length | undefined = topRightTmpBuf
        const bottomLeftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomLeftTmpBuf : Length | undefined = undefined
        if ((bottomLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomLeftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomLeftTmpBuf_ : string | double | Resource | undefined
            if (bottomLeftTmpBuf_UnionSelector == (0).toChar()) {
                bottomLeftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomLeftTmpBuf_UnionSelector == (1).toChar()) {
                bottomLeftTmpBuf_ = valueDeserializer.readFloat64()
            } else if (bottomLeftTmpBuf_UnionSelector == (2).toChar()) {
                bottomLeftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomLeftTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomLeftTmpBuf = (bottomLeftTmpBuf_ as string | double | Resource)
        }
        const bottomLeftTmpResult : Length | undefined = bottomLeftTmpBuf
        const bottomRightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomRightTmpBuf : Length | undefined = undefined
        if ((bottomRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomRightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomRightTmpBuf_ : string | double | Resource | undefined
            if (bottomRightTmpBuf_UnionSelector == (0).toChar()) {
                bottomRightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomRightTmpBuf_UnionSelector == (1).toChar()) {
                bottomRightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (bottomRightTmpBuf_UnionSelector == (2).toChar()) {
                bottomRightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomRightTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomRightTmpBuf = (bottomRightTmpBuf_ as string | double | Resource)
        }
        const bottomRightTmpResult : Length | undefined = bottomRightTmpBuf
        let value : BorderRadiuses = ({topLeft: topLeftTmpResult, topRight: topRightTmpResult, bottomLeft: bottomLeftTmpResult, bottomRight: bottomRightTmpResult} as BorderRadiuses)
        return value
    }
}
export class ConstraintSizeOptions_serializer {
    public static write(buffer: SerializerBase, value: ConstraintSizeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMinWidth  = value.minWidth
        if (valueHolderForMinWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinWidthTmpValue  = valueHolderForMinWidth!
            if (valueHolderForMinWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinWidthTmpValueForIdx0  = valueHolderForMinWidthTmpValue as string
                valueSerializer.writeString(valueHolderForMinWidthTmpValueForIdx0)
            } else if (valueHolderForMinWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinWidthTmpValueForIdx1  = valueHolderForMinWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMinWidthTmpValueForIdx1)
            } else if (valueHolderForMinWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMinWidthTmpValueForIdx2  = valueHolderForMinWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMinWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxWidth  = value.maxWidth
        if (valueHolderForMaxWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxWidthTmpValue  = valueHolderForMaxWidth!
            if (valueHolderForMaxWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxWidthTmpValueForIdx0  = valueHolderForMaxWidthTmpValue as string
                valueSerializer.writeString(valueHolderForMaxWidthTmpValueForIdx0)
            } else if (valueHolderForMaxWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxWidthTmpValueForIdx1  = valueHolderForMaxWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMaxWidthTmpValueForIdx1)
            } else if (valueHolderForMaxWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMaxWidthTmpValueForIdx2  = valueHolderForMaxWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMaxWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinHeight  = value.minHeight
        if (valueHolderForMinHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinHeightTmpValue  = valueHolderForMinHeight!
            if (valueHolderForMinHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinHeightTmpValueForIdx0  = valueHolderForMinHeightTmpValue as string
                valueSerializer.writeString(valueHolderForMinHeightTmpValueForIdx0)
            } else if (valueHolderForMinHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinHeightTmpValueForIdx1  = valueHolderForMinHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMinHeightTmpValueForIdx1)
            } else if (valueHolderForMinHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMinHeightTmpValueForIdx2  = valueHolderForMinHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMinHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxHeight  = value.maxHeight
        if (valueHolderForMaxHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxHeightTmpValue  = valueHolderForMaxHeight!
            if (valueHolderForMaxHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxHeightTmpValueForIdx0  = valueHolderForMaxHeightTmpValue as string
                valueSerializer.writeString(valueHolderForMaxHeightTmpValueForIdx0)
            } else if (valueHolderForMaxHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxHeightTmpValueForIdx1  = valueHolderForMaxHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMaxHeightTmpValueForIdx1)
            } else if (valueHolderForMaxHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMaxHeightTmpValueForIdx2  = valueHolderForMaxHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMaxHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ConstraintSizeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const minWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minWidthTmpBuf : Length | undefined = undefined
        if ((minWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let minWidthTmpBuf_ : string | double | Resource | undefined
            if (minWidthTmpBuf_UnionSelector == (0).toChar()) {
                minWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (minWidthTmpBuf_UnionSelector == (1).toChar()) {
                minWidthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (minWidthTmpBuf_UnionSelector == (2).toChar()) {
                minWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for minWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            minWidthTmpBuf = (minWidthTmpBuf_ as string | double | Resource)
        }
        const minWidthTmpResult : Length | undefined = minWidthTmpBuf
        const maxWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxWidthTmpBuf : Length | undefined = undefined
        if ((maxWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maxWidthTmpBuf_ : string | double | Resource | undefined
            if (maxWidthTmpBuf_UnionSelector == (0).toChar()) {
                maxWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (maxWidthTmpBuf_UnionSelector == (1).toChar()) {
                maxWidthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (maxWidthTmpBuf_UnionSelector == (2).toChar()) {
                maxWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for maxWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            maxWidthTmpBuf = (maxWidthTmpBuf_ as string | double | Resource)
        }
        const maxWidthTmpResult : Length | undefined = maxWidthTmpBuf
        const minHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minHeightTmpBuf : Length | undefined = undefined
        if ((minHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let minHeightTmpBuf_ : string | double | Resource | undefined
            if (minHeightTmpBuf_UnionSelector == (0).toChar()) {
                minHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (minHeightTmpBuf_UnionSelector == (1).toChar()) {
                minHeightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (minHeightTmpBuf_UnionSelector == (2).toChar()) {
                minHeightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for minHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            minHeightTmpBuf = (minHeightTmpBuf_ as string | double | Resource)
        }
        const minHeightTmpResult : Length | undefined = minHeightTmpBuf
        const maxHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxHeightTmpBuf : Length | undefined = undefined
        if ((maxHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maxHeightTmpBuf_ : string | double | Resource | undefined
            if (maxHeightTmpBuf_UnionSelector == (0).toChar()) {
                maxHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (maxHeightTmpBuf_UnionSelector == (1).toChar()) {
                maxHeightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (maxHeightTmpBuf_UnionSelector == (2).toChar()) {
                maxHeightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for maxHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            maxHeightTmpBuf = (maxHeightTmpBuf_ as string | double | Resource)
        }
        const maxHeightTmpResult : Length | undefined = maxHeightTmpBuf
        let value : ConstraintSizeOptions = ({minWidth: minWidthTmpResult, maxWidth: maxWidthTmpResult, minHeight: minHeightTmpResult, maxHeight: maxHeightTmpResult} as ConstraintSizeOptions)
        return value
    }
}
export class EdgeOutlineWidths_serializer {
    public static write(buffer: SerializerBase, value: EdgeOutlineWidths): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx0)
            } else if (valueHolderForTopTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as int32
                valueSerializer.writeInt32(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            if (valueHolderForRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRightTmpValueForIdx0  = valueHolderForRightTmpValue as string
                valueSerializer.writeString(valueHolderForRightTmpValueForIdx0)
            } else if (valueHolderForRightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRightTmpValueForIdx1  = valueHolderForRightTmpValue as number
                valueSerializer.writeNumber(valueHolderForRightTmpValueForIdx1)
            } else if (valueHolderForRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as string
                valueSerializer.writeString(valueHolderForBottomTmpValueForIdx0)
            } else if (valueHolderForBottomTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomTmpValueForIdx1  = valueHolderForBottomTmpValue as number
                valueSerializer.writeNumber(valueHolderForBottomTmpValueForIdx1)
            } else if (valueHolderForBottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as string
                valueSerializer.writeString(valueHolderForLeftTmpValueForIdx0)
            } else if (valueHolderForLeftTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeftTmpValueForIdx1  = valueHolderForLeftTmpValue as number
                valueSerializer.writeNumber(valueHolderForLeftTmpValueForIdx1)
            } else if (valueHolderForLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeOutlineWidths {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : Dimension | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : string | number | Resource | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (topTmpBuf_UnionSelector == (2).toChar()) {
                topTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as string | number | Resource)
        }
        const topTmpResult : Dimension | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : Dimension | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBuf_ : string | number | Resource | undefined
            if (rightTmpBuf_UnionSelector == (0).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (rightTmpBuf_UnionSelector == (1).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (rightTmpBuf_UnionSelector == (2).toChar()) {
                rightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for rightTmpBuf_ has to be chosen through deserialisation.")
            }
            rightTmpBuf = (rightTmpBuf_ as string | number | Resource)
        }
        const rightTmpResult : Dimension | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : Dimension | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBuf_ : string | number | Resource | undefined
            if (bottomTmpBuf_UnionSelector == (0).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomTmpBuf_UnionSelector == (1).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (bottomTmpBuf_UnionSelector == (2).toChar()) {
                bottomTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomTmpBuf = (bottomTmpBuf_ as string | number | Resource)
        }
        const bottomTmpResult : Dimension | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : Dimension | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : string | number | Resource | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (leftTmpBuf_UnionSelector == (2).toChar()) {
                leftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as string | number | Resource)
        }
        const leftTmpResult : Dimension | undefined = leftTmpBuf
        let value : EdgeOutlineWidths = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeOutlineWidths)
        return value
    }
}
export class Edges_serializer {
    public static write(buffer: SerializerBase, value: Edges): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx0)
            } else if (valueHolderForTopTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as int32
                valueSerializer.writeInt32(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as string
                valueSerializer.writeString(valueHolderForLeftTmpValueForIdx0)
            } else if (valueHolderForLeftTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeftTmpValueForIdx1  = valueHolderForLeftTmpValue as number
                valueSerializer.writeNumber(valueHolderForLeftTmpValueForIdx1)
            } else if (valueHolderForLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as string
                valueSerializer.writeString(valueHolderForBottomTmpValueForIdx0)
            } else if (valueHolderForBottomTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomTmpValueForIdx1  = valueHolderForBottomTmpValue as number
                valueSerializer.writeNumber(valueHolderForBottomTmpValueForIdx1)
            } else if (valueHolderForBottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            if (valueHolderForRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRightTmpValueForIdx0  = valueHolderForRightTmpValue as string
                valueSerializer.writeString(valueHolderForRightTmpValueForIdx0)
            } else if (valueHolderForRightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRightTmpValueForIdx1  = valueHolderForRightTmpValue as number
                valueSerializer.writeNumber(valueHolderForRightTmpValueForIdx1)
            } else if (valueHolderForRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Edges {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : Dimension | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : string | number | Resource | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (topTmpBuf_UnionSelector == (2).toChar()) {
                topTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as string | number | Resource)
        }
        const topTmpResult : Dimension | undefined = topTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : Dimension | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : string | number | Resource | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (leftTmpBuf_UnionSelector == (2).toChar()) {
                leftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as string | number | Resource)
        }
        const leftTmpResult : Dimension | undefined = leftTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : Dimension | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBuf_ : string | number | Resource | undefined
            if (bottomTmpBuf_UnionSelector == (0).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomTmpBuf_UnionSelector == (1).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (bottomTmpBuf_UnionSelector == (2).toChar()) {
                bottomTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomTmpBuf = (bottomTmpBuf_ as string | number | Resource)
        }
        const bottomTmpResult : Dimension | undefined = bottomTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : Dimension | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBuf_ : string | number | Resource | undefined
            if (rightTmpBuf_UnionSelector == (0).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (rightTmpBuf_UnionSelector == (1).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (rightTmpBuf_UnionSelector == (2).toChar()) {
                rightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for rightTmpBuf_ has to be chosen through deserialisation.")
            }
            rightTmpBuf = (rightTmpBuf_ as string | number | Resource)
        }
        const rightTmpResult : Dimension | undefined = rightTmpBuf
        let value : Edges = ({top: topTmpResult, left: leftTmpResult, bottom: bottomTmpResult, right: rightTmpResult} as Edges)
        return value
    }
}
export class EdgeWidths_serializer {
    public static write(buffer: SerializerBase, value: EdgeWidths): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx0)
            } else if (valueHolderForTopTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            if (valueHolderForRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRightTmpValueForIdx0  = valueHolderForRightTmpValue as string
                valueSerializer.writeString(valueHolderForRightTmpValueForIdx0)
            } else if (valueHolderForRightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRightTmpValueForIdx1  = valueHolderForRightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRightTmpValueForIdx1)
            } else if (valueHolderForRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as string
                valueSerializer.writeString(valueHolderForBottomTmpValueForIdx0)
            } else if (valueHolderForBottomTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomTmpValueForIdx1  = valueHolderForBottomTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBottomTmpValueForIdx1)
            } else if (valueHolderForBottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as string
                valueSerializer.writeString(valueHolderForLeftTmpValueForIdx0)
            } else if (valueHolderForLeftTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeftTmpValueForIdx1  = valueHolderForLeftTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLeftTmpValueForIdx1)
            } else if (valueHolderForLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeWidths {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : Length | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : string | double | Resource | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = valueDeserializer.readFloat64()
            } else if (topTmpBuf_UnionSelector == (2).toChar()) {
                topTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as string | double | Resource)
        }
        const topTmpResult : Length | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : Length | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBuf_ : string | double | Resource | undefined
            if (rightTmpBuf_UnionSelector == (0).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (rightTmpBuf_UnionSelector == (1).toChar()) {
                rightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (rightTmpBuf_UnionSelector == (2).toChar()) {
                rightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for rightTmpBuf_ has to be chosen through deserialisation.")
            }
            rightTmpBuf = (rightTmpBuf_ as string | double | Resource)
        }
        const rightTmpResult : Length | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : Length | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBuf_ : string | double | Resource | undefined
            if (bottomTmpBuf_UnionSelector == (0).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomTmpBuf_UnionSelector == (1).toChar()) {
                bottomTmpBuf_ = valueDeserializer.readFloat64()
            } else if (bottomTmpBuf_UnionSelector == (2).toChar()) {
                bottomTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomTmpBuf = (bottomTmpBuf_ as string | double | Resource)
        }
        const bottomTmpResult : Length | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : Length | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : string | double | Resource | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = valueDeserializer.readFloat64()
            } else if (leftTmpBuf_UnionSelector == (2).toChar()) {
                leftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as string | double | Resource)
        }
        const leftTmpResult : Length | undefined = leftTmpBuf
        let value : EdgeWidths = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeWidths)
        return value
    }
}
export class Font_serializer {
    public static write(buffer: SerializerBase, value: Font): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            if (valueHolderForSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValueForIdx0  = valueHolderForSizeTmpValue as string
                valueSerializer.writeString(valueHolderForSizeTmpValueForIdx0)
            } else if (valueHolderForSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValueForIdx1  = valueHolderForSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSizeTmpValueForIdx1)
            } else if (valueHolderForSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValueForIdx2  = valueHolderForSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWeight  = value.weight
        if (valueHolderForWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWeightTmpValue  = valueHolderForWeight!
            if (valueHolderForWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWeightTmpValueForIdx0  = valueHolderForWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForWeightTmpValueForIdx0.valueOf())
            } else if (valueHolderForWeightTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWeightTmpValueForIdx1  = valueHolderForWeightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForWeightTmpValueForIdx1)
            } else if (valueHolderForWeightTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWeightTmpValueForIdx2  = valueHolderForWeightTmpValue as string
                valueSerializer.writeString(valueHolderForWeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFamily  = value.family
        if (valueHolderForFamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFamilyTmpValue  = valueHolderForFamily!
            if (valueHolderForFamilyTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFamilyTmpValueForIdx0  = valueHolderForFamilyTmpValue as string
                valueSerializer.writeString(valueHolderForFamilyTmpValueForIdx0)
            } else if (valueHolderForFamilyTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFamilyTmpValueForIdx1  = valueHolderForFamilyTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFamilyTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as FontStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Font {
        let valueDeserializer : DeserializerBase = buffer
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sizeTmpBuf : Length | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBuf_ : string | double | Resource | undefined
            if (sizeTmpBuf_UnionSelector == (0).toChar()) {
                sizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (sizeTmpBuf_UnionSelector == (1).toChar()) {
                sizeTmpBuf_ = valueDeserializer.readFloat64()
            } else if (sizeTmpBuf_UnionSelector == (2).toChar()) {
                sizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for sizeTmpBuf_ has to be chosen through deserialisation.")
            }
            sizeTmpBuf = (sizeTmpBuf_ as string | double | Resource)
        }
        const sizeTmpResult : Length | undefined = sizeTmpBuf
        const weightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weightTmpBuf : FontWeight | int32 | string | undefined = undefined
        if ((weightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const weightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let weightTmpBuf_ : FontWeight | int32 | string | undefined
            if (weightTmpBuf_UnionSelector == (0).toChar()) {
                weightTmpBuf_ = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (weightTmpBuf_UnionSelector == (1).toChar()) {
                weightTmpBuf_ = valueDeserializer.readInt32()
            } else if (weightTmpBuf_UnionSelector == (2).toChar()) {
                weightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for weightTmpBuf_ has to be chosen through deserialisation.")
            }
            weightTmpBuf = (weightTmpBuf_ as FontWeight | int32 | string)
        }
        const weightTmpResult : FontWeight | int32 | string | undefined = weightTmpBuf
        const familyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let familyTmpBuf : string | Resource | undefined = undefined
        if ((familyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const familyTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let familyTmpBuf_ : string | Resource | undefined
            if (familyTmpBuf_UnionSelector == (0).toChar()) {
                familyTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (familyTmpBuf_UnionSelector == (1).toChar()) {
                familyTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for familyTmpBuf_ has to be chosen through deserialisation.")
            }
            familyTmpBuf = (familyTmpBuf_ as string | Resource)
        }
        const familyTmpResult : string | Resource | undefined = familyTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : FontStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = FontStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : FontStyle | undefined = styleTmpBuf
        let value : Font = ({size: sizeTmpResult, weight: weightTmpResult, family: familyTmpResult, style: styleTmpResult} as Font)
        return value
    }
}
export class MarkStyle_serializer {
    public static write(buffer: SerializerBase, value: MarkStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStrokeColor  = value.strokeColor
        if (valueHolderForStrokeColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeColorTmpValue  = valueHolderForStrokeColor!
            if (valueHolderForStrokeColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeColorTmpValueForIdx0  = valueHolderForStrokeColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForStrokeColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForStrokeColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeColorTmpValueForIdx1  = valueHolderForStrokeColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForStrokeColorTmpValueForIdx1)
            } else if (valueHolderForStrokeColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeColorTmpValueForIdx2  = valueHolderForStrokeColorTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeColorTmpValueForIdx2)
            } else if (valueHolderForStrokeColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForStrokeColorTmpValueForIdx3  = valueHolderForStrokeColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStrokeColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            if (valueHolderForSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValueForIdx0  = valueHolderForSizeTmpValue as string
                valueSerializer.writeString(valueHolderForSizeTmpValueForIdx0)
            } else if (valueHolderForSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValueForIdx1  = valueHolderForSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSizeTmpValueForIdx1)
            } else if (valueHolderForSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValueForIdx2  = valueHolderForSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            if (valueHolderForStrokeWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx0  = valueHolderForStrokeWidthTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeWidthTmpValueForIdx0)
            } else if (valueHolderForStrokeWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx1  = valueHolderForStrokeWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForStrokeWidthTmpValueForIdx1)
            } else if (valueHolderForStrokeWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx2  = valueHolderForStrokeWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MarkStyle {
        let valueDeserializer : DeserializerBase = buffer
        const strokeColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeColorTmpBuf : ResourceColor | undefined = undefined
        if ((strokeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let strokeColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (strokeColorTmpBuf_UnionSelector == (0).toChar()) {
                strokeColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (strokeColorTmpBuf_UnionSelector == (1).toChar()) {
                strokeColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (strokeColorTmpBuf_UnionSelector == (2).toChar()) {
                strokeColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (strokeColorTmpBuf_UnionSelector == (3).toChar()) {
                strokeColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for strokeColorTmpBuf_ has to be chosen through deserialisation.")
            }
            strokeColorTmpBuf = (strokeColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const strokeColorTmpResult : ResourceColor | undefined = strokeColorTmpBuf
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sizeTmpBuf : Length | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBuf_ : string | double | Resource | undefined
            if (sizeTmpBuf_UnionSelector == (0).toChar()) {
                sizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (sizeTmpBuf_UnionSelector == (1).toChar()) {
                sizeTmpBuf_ = valueDeserializer.readFloat64()
            } else if (sizeTmpBuf_UnionSelector == (2).toChar()) {
                sizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for sizeTmpBuf_ has to be chosen through deserialisation.")
            }
            sizeTmpBuf = (sizeTmpBuf_ as string | double | Resource)
        }
        const sizeTmpResult : Length | undefined = sizeTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidthTmpBuf : Length | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBuf_ : string | double | Resource | undefined
            if (strokeWidthTmpBuf_UnionSelector == (0).toChar()) {
                strokeWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBuf_UnionSelector == (1).toChar()) {
                strokeWidthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (strokeWidthTmpBuf_UnionSelector == (2).toChar()) {
                strokeWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for strokeWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            strokeWidthTmpBuf = (strokeWidthTmpBuf_ as string | double | Resource)
        }
        const strokeWidthTmpResult : Length | undefined = strokeWidthTmpBuf
        let value : MarkStyle = ({strokeColor: strokeColorTmpResult, size: sizeTmpResult, strokeWidth: strokeWidthTmpResult} as MarkStyle)
        return value
    }
}
export class OutlineRadiuses_serializer {
    public static write(buffer: SerializerBase, value: OutlineRadiuses): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTopLeft  = value.topLeft
        if (valueHolderForTopLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopLeftTmpValue  = valueHolderForTopLeft!
            if (valueHolderForTopLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopLeftTmpValueForIdx0  = valueHolderForTopLeftTmpValue as string
                valueSerializer.writeString(valueHolderForTopLeftTmpValueForIdx0)
            } else if (valueHolderForTopLeftTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopLeftTmpValueForIdx1  = valueHolderForTopLeftTmpValue as number
                valueSerializer.writeNumber(valueHolderForTopLeftTmpValueForIdx1)
            } else if (valueHolderForTopLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopLeftTmpValueForIdx2  = valueHolderForTopLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTopRight  = value.topRight
        if (valueHolderForTopRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopRightTmpValue  = valueHolderForTopRight!
            if (valueHolderForTopRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopRightTmpValueForIdx0  = valueHolderForTopRightTmpValue as string
                valueSerializer.writeString(valueHolderForTopRightTmpValueForIdx0)
            } else if (valueHolderForTopRightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopRightTmpValueForIdx1  = valueHolderForTopRightTmpValue as number
                valueSerializer.writeNumber(valueHolderForTopRightTmpValueForIdx1)
            } else if (valueHolderForTopRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopRightTmpValueForIdx2  = valueHolderForTopRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomLeft  = value.bottomLeft
        if (valueHolderForBottomLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomLeftTmpValue  = valueHolderForBottomLeft!
            if (valueHolderForBottomLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomLeftTmpValueForIdx0  = valueHolderForBottomLeftTmpValue as string
                valueSerializer.writeString(valueHolderForBottomLeftTmpValueForIdx0)
            } else if (valueHolderForBottomLeftTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomLeftTmpValueForIdx1  = valueHolderForBottomLeftTmpValue as number
                valueSerializer.writeNumber(valueHolderForBottomLeftTmpValueForIdx1)
            } else if (valueHolderForBottomLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomLeftTmpValueForIdx2  = valueHolderForBottomLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomRight  = value.bottomRight
        if (valueHolderForBottomRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomRightTmpValue  = valueHolderForBottomRight!
            if (valueHolderForBottomRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomRightTmpValueForIdx0  = valueHolderForBottomRightTmpValue as string
                valueSerializer.writeString(valueHolderForBottomRightTmpValueForIdx0)
            } else if (valueHolderForBottomRightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomRightTmpValueForIdx1  = valueHolderForBottomRightTmpValue as number
                valueSerializer.writeNumber(valueHolderForBottomRightTmpValueForIdx1)
            } else if (valueHolderForBottomRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomRightTmpValueForIdx2  = valueHolderForBottomRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OutlineRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topLeftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topLeftTmpBuf : Dimension | undefined = undefined
        if ((topLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topLeftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topLeftTmpBuf_ : string | number | Resource | undefined
            if (topLeftTmpBuf_UnionSelector == (0).toChar()) {
                topLeftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topLeftTmpBuf_UnionSelector == (1).toChar()) {
                topLeftTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (topLeftTmpBuf_UnionSelector == (2).toChar()) {
                topLeftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topLeftTmpBuf_ has to be chosen through deserialisation.")
            }
            topLeftTmpBuf = (topLeftTmpBuf_ as string | number | Resource)
        }
        const topLeftTmpResult : Dimension | undefined = topLeftTmpBuf
        const topRightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topRightTmpBuf : Dimension | undefined = undefined
        if ((topRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topRightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topRightTmpBuf_ : string | number | Resource | undefined
            if (topRightTmpBuf_UnionSelector == (0).toChar()) {
                topRightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topRightTmpBuf_UnionSelector == (1).toChar()) {
                topRightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (topRightTmpBuf_UnionSelector == (2).toChar()) {
                topRightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topRightTmpBuf_ has to be chosen through deserialisation.")
            }
            topRightTmpBuf = (topRightTmpBuf_ as string | number | Resource)
        }
        const topRightTmpResult : Dimension | undefined = topRightTmpBuf
        const bottomLeftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomLeftTmpBuf : Dimension | undefined = undefined
        if ((bottomLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomLeftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomLeftTmpBuf_ : string | number | Resource | undefined
            if (bottomLeftTmpBuf_UnionSelector == (0).toChar()) {
                bottomLeftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomLeftTmpBuf_UnionSelector == (1).toChar()) {
                bottomLeftTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (bottomLeftTmpBuf_UnionSelector == (2).toChar()) {
                bottomLeftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomLeftTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomLeftTmpBuf = (bottomLeftTmpBuf_ as string | number | Resource)
        }
        const bottomLeftTmpResult : Dimension | undefined = bottomLeftTmpBuf
        const bottomRightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomRightTmpBuf : Dimension | undefined = undefined
        if ((bottomRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomRightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomRightTmpBuf_ : string | number | Resource | undefined
            if (bottomRightTmpBuf_UnionSelector == (0).toChar()) {
                bottomRightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomRightTmpBuf_UnionSelector == (1).toChar()) {
                bottomRightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (bottomRightTmpBuf_UnionSelector == (2).toChar()) {
                bottomRightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomRightTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomRightTmpBuf = (bottomRightTmpBuf_ as string | number | Resource)
        }
        const bottomRightTmpResult : Dimension | undefined = bottomRightTmpBuf
        let value : OutlineRadiuses = ({topLeft: topLeftTmpResult, topRight: topRightTmpResult, bottomLeft: bottomLeftTmpResult, bottomRight: bottomRightTmpResult} as OutlineRadiuses)
        return value
    }
}
export class Padding_serializer {
    public static write(buffer: SerializerBase, value: Padding): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx0)
            } else if (valueHolderForTopTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            if (valueHolderForRightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRightTmpValueForIdx0  = valueHolderForRightTmpValue as string
                valueSerializer.writeString(valueHolderForRightTmpValueForIdx0)
            } else if (valueHolderForRightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRightTmpValueForIdx1  = valueHolderForRightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRightTmpValueForIdx1)
            } else if (valueHolderForRightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as string
                valueSerializer.writeString(valueHolderForBottomTmpValueForIdx0)
            } else if (valueHolderForBottomTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBottomTmpValueForIdx1  = valueHolderForBottomTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBottomTmpValueForIdx1)
            } else if (valueHolderForBottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as string
                valueSerializer.writeString(valueHolderForLeftTmpValueForIdx0)
            } else if (valueHolderForLeftTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeftTmpValueForIdx1  = valueHolderForLeftTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLeftTmpValueForIdx1)
            } else if (valueHolderForLeftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Padding {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : Length | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : string | double | Resource | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = valueDeserializer.readFloat64()
            } else if (topTmpBuf_UnionSelector == (2).toChar()) {
                topTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as string | double | Resource)
        }
        const topTmpResult : Length | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : Length | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBuf_ : string | double | Resource | undefined
            if (rightTmpBuf_UnionSelector == (0).toChar()) {
                rightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (rightTmpBuf_UnionSelector == (1).toChar()) {
                rightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (rightTmpBuf_UnionSelector == (2).toChar()) {
                rightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for rightTmpBuf_ has to be chosen through deserialisation.")
            }
            rightTmpBuf = (rightTmpBuf_ as string | double | Resource)
        }
        const rightTmpResult : Length | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : Length | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBuf_ : string | double | Resource | undefined
            if (bottomTmpBuf_UnionSelector == (0).toChar()) {
                bottomTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (bottomTmpBuf_UnionSelector == (1).toChar()) {
                bottomTmpBuf_ = valueDeserializer.readFloat64()
            } else if (bottomTmpBuf_UnionSelector == (2).toChar()) {
                bottomTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for bottomTmpBuf_ has to be chosen through deserialisation.")
            }
            bottomTmpBuf = (bottomTmpBuf_ as string | double | Resource)
        }
        const bottomTmpResult : Length | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : Length | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : string | double | Resource | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = valueDeserializer.readFloat64()
            } else if (leftTmpBuf_UnionSelector == (2).toChar()) {
                leftTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as string | double | Resource)
        }
        const leftTmpResult : Length | undefined = leftTmpBuf
        let value : Padding = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as Padding)
        return value
    }
}
export class Position_serializer {
    public static write(buffer: SerializerBase, value: Position): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        if (valueHolderForX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXTmpValue  = valueHolderForX!
            if (valueHolderForXTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXTmpValueForIdx0  = valueHolderForXTmpValue as string
                valueSerializer.writeString(valueHolderForXTmpValueForIdx0)
            } else if (valueHolderForXTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXTmpValueForIdx1  = valueHolderForXTmpValue as double
                valueSerializer.writeFloat64(valueHolderForXTmpValueForIdx1)
            } else if (valueHolderForXTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXTmpValueForIdx2  = valueHolderForXTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForXTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForY  = value.y
        if (valueHolderForY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForYTmpValue  = valueHolderForY!
            if (valueHolderForYTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForYTmpValueForIdx0  = valueHolderForYTmpValue as string
                valueSerializer.writeString(valueHolderForYTmpValueForIdx0)
            } else if (valueHolderForYTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForYTmpValueForIdx1  = valueHolderForYTmpValue as double
                valueSerializer.writeFloat64(valueHolderForYTmpValueForIdx1)
            } else if (valueHolderForYTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForYTmpValueForIdx2  = valueHolderForYTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForYTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Position {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xTmpBuf : Length | undefined = undefined
        if ((xTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let xTmpBuf_ : string | double | Resource | undefined
            if (xTmpBuf_UnionSelector == (0).toChar()) {
                xTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (xTmpBuf_UnionSelector == (1).toChar()) {
                xTmpBuf_ = valueDeserializer.readFloat64()
            } else if (xTmpBuf_UnionSelector == (2).toChar()) {
                xTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for xTmpBuf_ has to be chosen through deserialisation.")
            }
            xTmpBuf = (xTmpBuf_ as string | double | Resource)
        }
        const xTmpResult : Length | undefined = xTmpBuf
        const yTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let yTmpBuf : Length | undefined = undefined
        if ((yTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let yTmpBuf_ : string | double | Resource | undefined
            if (yTmpBuf_UnionSelector == (0).toChar()) {
                yTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (yTmpBuf_UnionSelector == (1).toChar()) {
                yTmpBuf_ = valueDeserializer.readFloat64()
            } else if (yTmpBuf_UnionSelector == (2).toChar()) {
                yTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for yTmpBuf_ has to be chosen through deserialisation.")
            }
            yTmpBuf = (yTmpBuf_ as string | double | Resource)
        }
        const yTmpResult : Length | undefined = yTmpBuf
        let value : Position = ({x: xTmpResult, y: yTmpResult} as Position)
        return value
    }
}
export class SizeOptions_serializer {
    public static write(buffer: SerializerBase, value: SizeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SizeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | double | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | double | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Length | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | double | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | double | Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        let value : SizeOptions = ({width: widthTmpResult, height: heightTmpResult} as SizeOptions)
        return value
    }
}
export class Area_serializer {
    public static write(buffer: SerializerBase, value: Area): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForWidthForIdx0  = valueHolderForWidth as string
            valueSerializer.writeString(valueHolderForWidthForIdx0)
        } else if (valueHolderForWidth instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForWidthForIdx1  = valueHolderForWidth as double
            valueSerializer.writeFloat64(valueHolderForWidthForIdx1)
        } else if (valueHolderForWidth instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForWidthForIdx2  = valueHolderForWidth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForWidthForIdx2)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForHeightForIdx0  = valueHolderForHeight as string
            valueSerializer.writeString(valueHolderForHeightForIdx0)
        } else if (valueHolderForHeight instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForHeightForIdx1  = valueHolderForHeight as double
            valueSerializer.writeFloat64(valueHolderForHeightForIdx1)
        } else if (valueHolderForHeight instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForHeightForIdx2  = valueHolderForHeight as Resource
            Resource_serializer.write(valueSerializer, valueHolderForHeightForIdx2)
        }
        const valueHolderForPosition  = value.position
        Position_serializer.write(valueSerializer, valueHolderForPosition)
        const valueHolderForGlobalPosition  = value.globalPosition
        Position_serializer.write(valueSerializer, valueHolderForGlobalPosition)
    }
    public static read(buffer: DeserializerBase): Area {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let widthTmpBuf : string | double | Resource | undefined
        if (widthTmpBufUnionSelector == (0).toChar()) {
            widthTmpBuf = (valueDeserializer.readString() as string)
        } else if (widthTmpBufUnionSelector == (1).toChar()) {
            widthTmpBuf = valueDeserializer.readFloat64()
        } else if (widthTmpBufUnionSelector == (2).toChar()) {
            widthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for widthTmpBuf has to be chosen through deserialisation.")
        }
        const widthTmpResult : Length = (widthTmpBuf as string | double | Resource)
        const heightTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let heightTmpBuf : string | double | Resource | undefined
        if (heightTmpBufUnionSelector == (0).toChar()) {
            heightTmpBuf = (valueDeserializer.readString() as string)
        } else if (heightTmpBufUnionSelector == (1).toChar()) {
            heightTmpBuf = valueDeserializer.readFloat64()
        } else if (heightTmpBufUnionSelector == (2).toChar()) {
            heightTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for heightTmpBuf has to be chosen through deserialisation.")
        }
        const heightTmpResult : Length = (heightTmpBuf as string | double | Resource)
        const positionTmpResult : Position = Position_serializer.read(valueDeserializer)
        const globalPositionTmpResult : Position = Position_serializer.read(valueDeserializer)
        let value : Area = ({width: widthTmpResult, height: heightTmpResult, position: positionTmpResult, globalPosition: globalPositionTmpResult} as Area)
        return value
    }
}
export class BorderOptions_serializer {
    public static write(buffer: SerializerBase, value: BorderOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof Length) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as Length
                if (valueHolderForWidthTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx0  = valueHolderForWidthTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1ForIdx0)
                } else if (valueHolderForWidthTmpValueForIdx1 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx1  = valueHolderForWidthTmpValueForIdx1 as double
                    valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1ForIdx1)
                } else if (valueHolderForWidthTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx2  = valueHolderForWidthTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx1ForIdx2)
                }
            } else if (valueHolderForWidthTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx0)
            } else if (valueHolderForColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as ResourceColor
                if (valueHolderForColorTmpValueForIdx1 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx0  = valueHolderForColorTmpValueForIdx1 as Color
                    valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1ForIdx0.getOrdinal())
                } else if (valueHolderForColorTmpValueForIdx1 instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx1  = valueHolderForColorTmpValueForIdx1 as int32
                    valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1ForIdx1)
                } else if (valueHolderForColorTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx2  = valueHolderForColorTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForColorTmpValueForIdx1ForIdx2)
                } else if (valueHolderForColorTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx3  = valueHolderForColorTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx1ForIdx3)
                }
            } else if (valueHolderForColorTmpValue instanceof LocalizedEdgeColors) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof Length) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as Length
                if (valueHolderForRadiusTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx0  = valueHolderForRadiusTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1ForIdx0)
                } else if (valueHolderForRadiusTmpValueForIdx1 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx1  = valueHolderForRadiusTmpValueForIdx1 as double
                    valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx1ForIdx1)
                } else if (valueHolderForRadiusTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx2  = valueHolderForRadiusTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1ForIdx2)
                }
            } else if (valueHolderForRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRadiusTmpValueForIdx2  = valueHolderForRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = valueHolderForStyle!
            if (valueHolderForStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStyleTmpValueForIdx0  = valueHolderForStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForStyleTmpValueForIdx0)
            } else if (valueHolderForStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStyleTmpValueForIdx1  = valueHolderForStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForStyleTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDashGap  = value.dashGap
        if (valueHolderForDashGap !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDashGapTmpValue  = valueHolderForDashGap!
            if (valueHolderForDashGapTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForDashGapTmpValueForIdx0  = valueHolderForDashGapTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForDashGapTmpValueForIdx0)
            } else if (valueHolderForDashGapTmpValue instanceof LengthMetrics) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForDashGapTmpValueForIdx1  = valueHolderForDashGapTmpValue as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, valueHolderForDashGapTmpValueForIdx1)
            } else if (valueHolderForDashGapTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForDashGapTmpValueForIdx2  = valueHolderForDashGapTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForDashGapTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDashWidth  = value.dashWidth
        if (valueHolderForDashWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDashWidthTmpValue  = valueHolderForDashWidth!
            if (valueHolderForDashWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForDashWidthTmpValueForIdx0  = valueHolderForDashWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForDashWidthTmpValueForIdx0)
            } else if (valueHolderForDashWidthTmpValue instanceof LengthMetrics) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForDashWidthTmpValueForIdx1  = valueHolderForDashWidthTmpValue as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, valueHolderForDashWidthTmpValueForIdx1)
            } else if (valueHolderForDashWidthTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForDashWidthTmpValueForIdx2  = valueHolderForDashWidthTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForDashWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInForeground  = value.showInForeground
        if (valueHolderForShowInForeground !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInForegroundTmpValue  = valueHolderForShowInForeground!
            valueSerializer.writeBoolean(valueHolderForShowInForegroundTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BorderOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : EdgeWidths | Length | LocalizedEdgeWidths | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : EdgeWidths | Length | LocalizedEdgeWidths | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                const widthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let widthTmpBuf_BufU : string | double | Resource | undefined
                if (widthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    widthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (widthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    widthTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (widthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    widthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for widthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                widthTmpBuf_ = (widthTmpBuf_BufU as string | double | Resource)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as EdgeWidths | Length | LocalizedEdgeWidths)
        }
        const widthTmpResult : EdgeWidths | Length | LocalizedEdgeWidths | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                const colorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBuf_BufU : Color | int32 | string | Resource | undefined
                if (colorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    colorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (colorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    colorTmpBuf_BufU = valueDeserializer.readInt32()
                } else if (colorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    colorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (colorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    colorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for colorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                colorTmpBuf_ = (colorTmpBuf_BufU as Color | int32 | string | Resource)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as EdgeColors | ResourceColor | LocalizedEdgeColors)
        }
        const colorTmpResult : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = colorTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                radiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                const radiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBuf_BufU : string | double | Resource | undefined
                if (radiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    radiusTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (radiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    radiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for radiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                radiusTmpBuf_ = (radiusTmpBuf_BufU as string | double | Resource)
            } else if (radiusTmpBuf_UnionSelector == (2).toChar()) {
                radiusTmpBuf_ = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for radiusTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusTmpBuf = (radiusTmpBuf_ as BorderRadiuses | Length | LocalizedBorderRadiuses)
        }
        const radiusTmpResult : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined = radiusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : EdgeStyles | BorderStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const styleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let styleTmpBuf_ : EdgeStyles | BorderStyle | undefined
            if (styleTmpBuf_UnionSelector == (0).toChar()) {
                styleTmpBuf_ = EdgeStyles_serializer.read(valueDeserializer)
            } else if (styleTmpBuf_UnionSelector == (1).toChar()) {
                styleTmpBuf_ = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for styleTmpBuf_ has to be chosen through deserialisation.")
            }
            styleTmpBuf = (styleTmpBuf_ as EdgeStyles | BorderStyle)
        }
        const styleTmpResult : EdgeStyles | BorderStyle | undefined = styleTmpBuf
        const dashGapTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dashGapTmpBuf : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = undefined
        if ((dashGapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const dashGapTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let dashGapTmpBuf_ : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
            if (dashGapTmpBuf_UnionSelector == (0).toChar()) {
                dashGapTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else if (dashGapTmpBuf_UnionSelector == (1).toChar()) {
                dashGapTmpBuf_ = LengthMetrics_serializer.read(valueDeserializer)
            } else if (dashGapTmpBuf_UnionSelector == (2).toChar()) {
                dashGapTmpBuf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for dashGapTmpBuf_ has to be chosen through deserialisation.")
            }
            dashGapTmpBuf = (dashGapTmpBuf_ as EdgeWidths | LengthMetrics | LocalizedEdgeWidths)
        }
        const dashGapTmpResult : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = dashGapTmpBuf
        const dashWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dashWidthTmpBuf : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = undefined
        if ((dashWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const dashWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let dashWidthTmpBuf_ : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
            if (dashWidthTmpBuf_UnionSelector == (0).toChar()) {
                dashWidthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else if (dashWidthTmpBuf_UnionSelector == (1).toChar()) {
                dashWidthTmpBuf_ = LengthMetrics_serializer.read(valueDeserializer)
            } else if (dashWidthTmpBuf_UnionSelector == (2).toChar()) {
                dashWidthTmpBuf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for dashWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            dashWidthTmpBuf = (dashWidthTmpBuf_ as EdgeWidths | LengthMetrics | LocalizedEdgeWidths)
        }
        const dashWidthTmpResult : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = dashWidthTmpBuf
        const showInForegroundTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInForegroundTmpBuf : boolean | undefined = undefined
        if ((showInForegroundTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInForegroundTmpBuf = valueDeserializer.readBoolean()
        }
        const showInForegroundTmpResult : boolean | undefined = showInForegroundTmpBuf
        let value : BorderOptions = ({width: widthTmpResult, color: colorTmpResult, radius: radiusTmpResult, style: styleTmpResult, dashGap: dashGapTmpResult, dashWidth: dashWidthTmpResult, showInForeground: showInForegroundTmpResult} as BorderOptions)
        return value
    }
}
export class OutlineOptions_serializer {
    public static write(buffer: SerializerBase, value: OutlineOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof EdgeOutlineWidths) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as EdgeOutlineWidths
                EdgeOutlineWidths_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as Dimension
                if (valueHolderForWidthTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx0  = valueHolderForWidthTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1ForIdx0)
                } else if (valueHolderForWidthTmpValueForIdx1 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx1  = valueHolderForWidthTmpValueForIdx1 as number
                    valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1ForIdx1)
                } else if (valueHolderForWidthTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx2  = valueHolderForWidthTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx1ForIdx2)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx0)
            } else if (valueHolderForColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as ResourceColor
                if (valueHolderForColorTmpValueForIdx1 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx0  = valueHolderForColorTmpValueForIdx1 as Color
                    valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1ForIdx0.getOrdinal())
                } else if (valueHolderForColorTmpValueForIdx1 instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx1  = valueHolderForColorTmpValueForIdx1 as int32
                    valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1ForIdx1)
                } else if (valueHolderForColorTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx2  = valueHolderForColorTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForColorTmpValueForIdx1ForIdx2)
                } else if (valueHolderForColorTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx3  = valueHolderForColorTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx1ForIdx3)
                }
            } else if (valueHolderForColorTmpValue instanceof LocalizedEdgeColors) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof OutlineRadiuses) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as OutlineRadiuses
                OutlineRadiuses_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as Dimension
                if (valueHolderForRadiusTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx0  = valueHolderForRadiusTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1ForIdx0)
                } else if (valueHolderForRadiusTmpValueForIdx1 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx1  = valueHolderForRadiusTmpValueForIdx1 as number
                    valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx1ForIdx1)
                } else if (valueHolderForRadiusTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx2  = valueHolderForRadiusTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1ForIdx2)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = valueHolderForStyle!
            if (valueHolderForStyleTmpValue instanceof EdgeOutlineStyles) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStyleTmpValueForIdx0  = valueHolderForStyleTmpValue as EdgeOutlineStyles
                EdgeOutlineStyles_serializer.write(valueSerializer, valueHolderForStyleTmpValueForIdx0)
            } else if (valueHolderForStyleTmpValue instanceof OutlineStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStyleTmpValueForIdx1  = valueHolderForStyleTmpValue as OutlineStyle
                valueSerializer.writeInt32(valueHolderForStyleTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OutlineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : EdgeOutlineWidths | Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : EdgeOutlineWidths | Dimension | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = EdgeOutlineWidths_serializer.read(valueDeserializer)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                const widthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let widthTmpBuf_BufU : string | number | Resource | undefined
                if (widthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    widthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (widthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    widthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (widthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    widthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for widthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                widthTmpBuf_ = (widthTmpBuf_BufU as string | number | Resource)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as EdgeOutlineWidths | Dimension)
        }
        const widthTmpResult : EdgeOutlineWidths | Dimension | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                const colorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBuf_BufU : Color | int32 | string | Resource | undefined
                if (colorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    colorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (colorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    colorTmpBuf_BufU = valueDeserializer.readInt32()
                } else if (colorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    colorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (colorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    colorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for colorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                colorTmpBuf_ = (colorTmpBuf_BufU as Color | int32 | string | Resource)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as EdgeColors | ResourceColor | LocalizedEdgeColors)
        }
        const colorTmpResult : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = colorTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : OutlineRadiuses | Dimension | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : OutlineRadiuses | Dimension | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                radiusTmpBuf_ = OutlineRadiuses_serializer.read(valueDeserializer)
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                const radiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBuf_BufU : string | number | Resource | undefined
                if (radiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (radiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    radiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for radiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                radiusTmpBuf_ = (radiusTmpBuf_BufU as string | number | Resource)
            } else {
                throw new Error("One of the branches for radiusTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusTmpBuf = (radiusTmpBuf_ as OutlineRadiuses | Dimension)
        }
        const radiusTmpResult : OutlineRadiuses | Dimension | undefined = radiusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : EdgeOutlineStyles | OutlineStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const styleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let styleTmpBuf_ : EdgeOutlineStyles | OutlineStyle | undefined
            if (styleTmpBuf_UnionSelector == (0).toChar()) {
                styleTmpBuf_ = EdgeOutlineStyles_serializer.read(valueDeserializer)
            } else if (styleTmpBuf_UnionSelector == (1).toChar()) {
                styleTmpBuf_ = OutlineStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for styleTmpBuf_ has to be chosen through deserialisation.")
            }
            styleTmpBuf = (styleTmpBuf_ as EdgeOutlineStyles | OutlineStyle)
        }
        const styleTmpResult : EdgeOutlineStyles | OutlineStyle | undefined = styleTmpBuf
        let value : OutlineOptions = ({width: widthTmpResult, color: colorTmpResult, radius: radiusTmpResult, style: styleTmpResult} as OutlineOptions)
        return value
    }
}

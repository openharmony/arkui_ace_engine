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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Resource as global_resource_Resource } from 'global.resource'
import { extractors } from '#handwritten'
import { default as drawing } from '@ohos.graphics.drawing'
import { LengthMetrics as arkui_Graphics_LengthMetrics, LengthMetricsUnit as arkui_Graphics_LengthMetricsUnit, ColorMetrics as arkui_Graphics_ColorMetrics } from '@arkui.Graphics'
import { Color as arkui_component_enums_Color, BorderStyle, FontWeight, FontStyle, DividerMode } from './enums'
import { OutlineStyle } from './common'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ColorFilterInternal {
    public static fromPtr(ptr: KPointer): ColorFilter {
        return new ColorFilter(MaterializedBaseTag.NOP, ptr)
    }
}
export class ColorFilter implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ColorFilter.getFinalizer())
    }
    constructor(value: Array<double>) {
        this(MaterializedBaseTag.NOP, ColorFilter.construct(value))
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
export type Resource = global_resource_Resource;
export type Length = string | double | Resource;
export type PX = string;
export type VP = string | double;
export type FP = string;
export type LPX = string;
export type Percentage = string;
export type Degree = string;
export type Dimension = string | number | global_resource_Resource;
export type ResourceStr = string | Resource;
export type DrawingCanvas = drawing.Canvas;
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
export type ResourceColor = arkui_component_enums_Color | int32 | string | Resource;
export interface LengthConstrain {
    minLength: Length;
    maxLength: Length;
}
export type VoidCallback = () => void;
export type LengthMetricsUnit = arkui_Graphics_LengthMetricsUnit;
export type LengthMetrics = arkui_Graphics_LengthMetrics;
export type ColorMetrics = arkui_Graphics_ColorMetrics;
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
        const accessibilityPreferredTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
        const horizontalTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let horizontalTmpBuf : double | undefined = undefined
        if ((horizontalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            horizontalTmpBuf = valueDeserializer.readFloat64()
        }
        const horizontalTmpResult : double | undefined = horizontalTmpBuf
        const verticalTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
        const horizontalTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let horizontalTmpBuf : double | undefined = undefined
        if ((horizontalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            horizontalTmpBuf = valueDeserializer.readFloat64()
        }
        const horizontalTmpResult : double | undefined = horizontalTmpBuf
        const verticalTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let verticalTmpBuf : double | undefined = undefined
        if ((verticalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            verticalTmpBuf = valueDeserializer.readFloat64()
        }
        const verticalTmpResult : double | undefined = verticalTmpBuf
        let value : ChainWeightOptions = ({horizontal: horizontalTmpResult, vertical: verticalTmpResult} as ChainWeightOptions)
        return value
    }
}
export class DirectionalEdgesT_F64_serializer {
    public static write(buffer: SerializerBase, value: DirectionalEdgesT<double>): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        valueSerializer.writeFloat64(valueHolderForStart)
        const valueHolderForEnd  = value.end
        valueSerializer.writeFloat64(valueHolderForEnd)
        const valueHolderForTop  = value.top
        valueSerializer.writeFloat64(valueHolderForTop)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeFloat64(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): DirectionalEdgesT<double> {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpResult : double = valueDeserializer.readFloat64()
        const endTmpResult : double = valueDeserializer.readFloat64()
        const topTmpResult : double = valueDeserializer.readFloat64()
        const bottomTmpResult : double = valueDeserializer.readFloat64()
        let value : DirectionalEdgesT<double> = ({start: startTmpResult, end: endTmpResult, top: topTmpResult, bottom: bottomTmpResult} as DirectionalEdgesT<double>)
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
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : OutlineStyle | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const topTmpResult : OutlineStyle | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : OutlineStyle | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            rightTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const rightTmpResult : OutlineStyle | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : OutlineStyle | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = OutlineStyle.fromValue(valueDeserializer.readInt32())
        }
        const bottomTmpResult : OutlineStyle | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : BorderStyle | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const topTmpResult : BorderStyle | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : BorderStyle | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            rightTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const rightTmpResult : BorderStyle | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : BorderStyle | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = BorderStyle.fromValue(valueDeserializer.readInt32())
        }
        const bottomTmpResult : BorderStyle | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStartMargin  = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue  = valueHolderForStartMargin!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStartMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin  = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue  = valueHolderForEndMargin!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForEndMarginTmpValue)
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
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf : LengthMetrics | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeWidthTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeWidthTmpResult : LengthMetrics | undefined = strokeWidthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startMarginTmpBuf : LengthMetrics | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startMarginTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const startMarginTmpResult : LengthMetrics | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endMarginTmpBuf : LengthMetrics | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endMarginTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const endMarginTmpResult : LengthMetrics | undefined = endMarginTmpBuf
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
            if (valueHolderForTopTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForTopTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            if (valueHolderForRightTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRightTmpValueForIdx0  = valueHolderForRightTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForRightTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBottomTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForLeftTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeColors {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : ResourceColor | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (topTmpBufOptUnionSelector == (0).toByte()) {
                topTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (topTmpBufOptUnionSelector == (1).toByte()) {
                topTmpBufOpt = valueDeserializer.readInt32()
            } else if (topTmpBufOptUnionSelector == (2).toByte()) {
                topTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topTmpBufOptUnionSelector == (3).toByte()) {
                topTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topTmpBufOpt has to be chosen through deserialisation.')
            }
            topTmpBuf = (topTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const topTmpResult : ResourceColor | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : ResourceColor | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (rightTmpBufOptUnionSelector == (0).toByte()) {
                rightTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (rightTmpBufOptUnionSelector == (1).toByte()) {
                rightTmpBufOpt = valueDeserializer.readInt32()
            } else if (rightTmpBufOptUnionSelector == (2).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (rightTmpBufOptUnionSelector == (3).toByte()) {
                rightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for rightTmpBufOpt has to be chosen through deserialisation.')
            }
            rightTmpBuf = (rightTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const rightTmpResult : ResourceColor | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : ResourceColor | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (bottomTmpBufOptUnionSelector == (0).toByte()) {
                bottomTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (bottomTmpBufOptUnionSelector == (1).toByte()) {
                bottomTmpBufOpt = valueDeserializer.readInt32()
            } else if (bottomTmpBufOptUnionSelector == (2).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomTmpBufOptUnionSelector == (3).toByte()) {
                bottomTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomTmpBuf = (bottomTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const bottomTmpResult : ResourceColor | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leftTmpBuf : ResourceColor | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (leftTmpBufOptUnionSelector == (0).toByte()) {
                leftTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (leftTmpBufOptUnionSelector == (1).toByte()) {
                leftTmpBufOpt = valueDeserializer.readInt32()
            } else if (leftTmpBufOptUnionSelector == (2).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (leftTmpBufOptUnionSelector == (3).toByte()) {
                leftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leftTmpBufOpt has to be chosen through deserialisation.')
            }
            leftTmpBuf = (leftTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
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
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForMinLengthForIdx2)
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
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForMaxLengthForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): LengthConstrain {
        let valueDeserializer : DeserializerBase = buffer
        const minLengthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let minLengthTmpBuf : string | double | Resource | undefined
        if (minLengthTmpBufUnionSelector == (0).toByte()) {
            minLengthTmpBuf = (valueDeserializer.readString() as string)
        } else if (minLengthTmpBufUnionSelector == (1).toByte()) {
            minLengthTmpBuf = valueDeserializer.readFloat64()
        } else if (minLengthTmpBufUnionSelector == (2).toByte()) {
            minLengthTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for minLengthTmpBuf has to be chosen through deserialisation.')
        }
        const minLengthTmpResult : Length = (minLengthTmpBuf as string | double | Resource)
        const maxLengthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let maxLengthTmpBuf : string | double | Resource | undefined
        if (maxLengthTmpBufUnionSelector == (0).toByte()) {
            maxLengthTmpBuf = (valueDeserializer.readString() as string)
        } else if (maxLengthTmpBufUnionSelector == (1).toByte()) {
            maxLengthTmpBuf = valueDeserializer.readFloat64()
        } else if (maxLengthTmpBufUnionSelector == (2).toByte()) {
            maxLengthTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for maxLengthTmpBuf has to be chosen through deserialisation.')
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
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTopEnd  = value.topEnd
        if (valueHolderForTopEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopEndTmpValue  = valueHolderForTopEnd!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomStart  = value.bottomStart
        if (valueHolderForBottomStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomStartTmpValue  = valueHolderForBottomStart!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottomEnd  = value.bottomEnd
        if (valueHolderForBottomEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomEndTmpValue  = valueHolderForBottomEnd!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedBorderRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topStartTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topStartTmpBuf : LengthMetrics | undefined = undefined
        if ((topStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topStartTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const topStartTmpResult : LengthMetrics | undefined = topStartTmpBuf
        const topEndTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topEndTmpBuf : LengthMetrics | undefined = undefined
        if ((topEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topEndTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const topEndTmpResult : LengthMetrics | undefined = topEndTmpBuf
        const bottomStartTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomStartTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomStartTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomStartTmpResult : LengthMetrics | undefined = bottomStartTmpBuf
        const bottomEndTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomEndTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomEndTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
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
            if (valueHolderForTopTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForTopTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            if (valueHolderForEndTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndTmpValueForIdx0  = valueHolderForEndTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForEndTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForEndTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            if (valueHolderForBottomTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBottomTmpValueForIdx0  = valueHolderForBottomTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBottomTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            if (valueHolderForStartTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartTmpValueForIdx0  = valueHolderForStartTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForStartTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStartTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdgeColors {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : ResourceColor | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (topTmpBufOptUnionSelector == (0).toByte()) {
                topTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (topTmpBufOptUnionSelector == (1).toByte()) {
                topTmpBufOpt = valueDeserializer.readInt32()
            } else if (topTmpBufOptUnionSelector == (2).toByte()) {
                topTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topTmpBufOptUnionSelector == (3).toByte()) {
                topTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topTmpBufOpt has to be chosen through deserialisation.')
            }
            topTmpBuf = (topTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const topTmpResult : ResourceColor | undefined = topTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : ResourceColor | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let endTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (endTmpBufOptUnionSelector == (0).toByte()) {
                endTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (endTmpBufOptUnionSelector == (1).toByte()) {
                endTmpBufOpt = valueDeserializer.readInt32()
            } else if (endTmpBufOptUnionSelector == (2).toByte()) {
                endTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (endTmpBufOptUnionSelector == (3).toByte()) {
                endTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for endTmpBufOpt has to be chosen through deserialisation.')
            }
            endTmpBuf = (endTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const endTmpResult : ResourceColor | undefined = endTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : ResourceColor | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (bottomTmpBufOptUnionSelector == (0).toByte()) {
                bottomTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (bottomTmpBufOptUnionSelector == (1).toByte()) {
                bottomTmpBufOpt = valueDeserializer.readInt32()
            } else if (bottomTmpBufOptUnionSelector == (2).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomTmpBufOptUnionSelector == (3).toByte()) {
                bottomTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomTmpBuf = (bottomTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const bottomTmpResult : ResourceColor | undefined = bottomTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : ResourceColor | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let startTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (startTmpBufOptUnionSelector == (0).toByte()) {
                startTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (startTmpBufOptUnionSelector == (1).toByte()) {
                startTmpBufOpt = valueDeserializer.readInt32()
            } else if (startTmpBufOptUnionSelector == (2).toByte()) {
                startTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (startTmpBufOptUnionSelector == (3).toByte()) {
                startTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for startTmpBufOpt has to be chosen through deserialisation.')
            }
            startTmpBuf = (startTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
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
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdges {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const startTmpResult : LengthMetrics | undefined = startTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : LengthMetrics | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
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
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedEdgeWidths {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : LengthMetrics | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const endTmpResult : LengthMetrics | undefined = endTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
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
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedPadding {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : LengthMetrics | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const endTmpResult : LengthMetrics | undefined = endTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
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
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedPosition {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : LengthMetrics | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const startTmpResult : LengthMetrics | undefined = startTmpBuf
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
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
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForDxForIdx2)
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
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForDyForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): Offset {
        let valueDeserializer : DeserializerBase = buffer
        const dxTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let dxTmpBuf : string | double | Resource | undefined
        if (dxTmpBufUnionSelector == (0).toByte()) {
            dxTmpBuf = (valueDeserializer.readString() as string)
        } else if (dxTmpBufUnionSelector == (1).toByte()) {
            dxTmpBuf = valueDeserializer.readFloat64()
        } else if (dxTmpBufUnionSelector == (2).toByte()) {
            dxTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for dxTmpBuf has to be chosen through deserialisation.')
        }
        const dxTmpResult : Length = (dxTmpBuf as string | double | Resource)
        const dyTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let dyTmpBuf : string | double | Resource | undefined
        if (dyTmpBufUnionSelector == (0).toByte()) {
            dyTmpBuf = (valueDeserializer.readString() as string)
        } else if (dyTmpBufUnionSelector == (1).toByte()) {
            dyTmpBuf = valueDeserializer.readFloat64()
        } else if (dyTmpBufUnionSelector == (2).toByte()) {
            dyTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for dyTmpBuf has to be chosen through deserialisation.')
        }
        const dyTmpResult : Length = (dyTmpBuf as string | double | Resource)
        let value : Offset = ({dx: dxTmpResult, dy: dyTmpResult} as Offset)
        return value
    }
}
export class arkui_component_units_Font_serializer {
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFamilyTmpValueForIdx1)
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
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf : Length | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBufOpt : string | double | Resource | undefined
            if (sizeTmpBufOptUnionSelector == (0).toByte()) {
                sizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptUnionSelector == (1).toByte()) {
                sizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (sizeTmpBufOptUnionSelector == (2).toByte()) {
                sizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOpt has to be chosen through deserialisation.')
            }
            sizeTmpBuf = (sizeTmpBufOpt as string | double | Resource)
        }
        const sizeTmpResult : Length | undefined = sizeTmpBuf
        const weightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let weightTmpBuf : FontWeight | int32 | string | undefined = undefined
        if ((weightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const weightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let weightTmpBufOpt : FontWeight | int32 | string | undefined
            if (weightTmpBufOptUnionSelector == (0).toByte()) {
                weightTmpBufOpt = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (weightTmpBufOptUnionSelector == (1).toByte()) {
                weightTmpBufOpt = valueDeserializer.readInt32()
            } else if (weightTmpBufOptUnionSelector == (2).toByte()) {
                weightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for weightTmpBufOpt has to be chosen through deserialisation.')
            }
            weightTmpBuf = (weightTmpBufOpt as FontWeight | int32 | string)
        }
        const weightTmpResult : FontWeight | int32 | string | undefined = weightTmpBuf
        const familyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let familyTmpBuf : string | Resource | undefined = undefined
        if ((familyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const familyTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let familyTmpBufOpt : string | Resource | undefined
            if (familyTmpBufOptUnionSelector == (0).toByte()) {
                familyTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (familyTmpBufOptUnionSelector == (1).toByte()) {
                familyTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for familyTmpBufOpt has to be chosen through deserialisation.')
            }
            familyTmpBuf = (familyTmpBufOpt as string | Resource)
        }
        const familyTmpResult : string | Resource | undefined = familyTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : FontStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = FontStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : FontStyle | undefined = styleTmpBuf
        let value : Font = ({size: sizeTmpResult, weight: weightTmpResult, family: familyTmpResult, style: styleTmpResult} as Font)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopLeftTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopRightTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomLeftTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BorderRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topLeftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topLeftTmpBuf : Length | undefined = undefined
        if ((topLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topLeftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topLeftTmpBufOpt : string | double | Resource | undefined
            if (topLeftTmpBufOptUnionSelector == (0).toByte()) {
                topLeftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topLeftTmpBufOptUnionSelector == (1).toByte()) {
                topLeftTmpBufOpt = valueDeserializer.readFloat64()
            } else if (topLeftTmpBufOptUnionSelector == (2).toByte()) {
                topLeftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topLeftTmpBufOpt has to be chosen through deserialisation.')
            }
            topLeftTmpBuf = (topLeftTmpBufOpt as string | double | Resource)
        }
        const topLeftTmpResult : Length | undefined = topLeftTmpBuf
        const topRightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topRightTmpBuf : Length | undefined = undefined
        if ((topRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topRightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topRightTmpBufOpt : string | double | Resource | undefined
            if (topRightTmpBufOptUnionSelector == (0).toByte()) {
                topRightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topRightTmpBufOptUnionSelector == (1).toByte()) {
                topRightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (topRightTmpBufOptUnionSelector == (2).toByte()) {
                topRightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topRightTmpBufOpt has to be chosen through deserialisation.')
            }
            topRightTmpBuf = (topRightTmpBufOpt as string | double | Resource)
        }
        const topRightTmpResult : Length | undefined = topRightTmpBuf
        const bottomLeftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomLeftTmpBuf : Length | undefined = undefined
        if ((bottomLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomLeftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomLeftTmpBufOpt : string | double | Resource | undefined
            if (bottomLeftTmpBufOptUnionSelector == (0).toByte()) {
                bottomLeftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomLeftTmpBufOptUnionSelector == (1).toByte()) {
                bottomLeftTmpBufOpt = valueDeserializer.readFloat64()
            } else if (bottomLeftTmpBufOptUnionSelector == (2).toByte()) {
                bottomLeftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomLeftTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomLeftTmpBuf = (bottomLeftTmpBufOpt as string | double | Resource)
        }
        const bottomLeftTmpResult : Length | undefined = bottomLeftTmpBuf
        const bottomRightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomRightTmpBuf : Length | undefined = undefined
        if ((bottomRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomRightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomRightTmpBufOpt : string | double | Resource | undefined
            if (bottomRightTmpBufOptUnionSelector == (0).toByte()) {
                bottomRightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomRightTmpBufOptUnionSelector == (1).toByte()) {
                bottomRightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (bottomRightTmpBufOptUnionSelector == (2).toByte()) {
                bottomRightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomRightTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomRightTmpBuf = (bottomRightTmpBufOpt as string | double | Resource)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMinWidthTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMaxWidthTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMinHeightTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMaxHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ConstraintSizeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const minWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let minWidthTmpBuf : Length | undefined = undefined
        if ((minWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let minWidthTmpBufOpt : string | double | Resource | undefined
            if (minWidthTmpBufOptUnionSelector == (0).toByte()) {
                minWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (minWidthTmpBufOptUnionSelector == (1).toByte()) {
                minWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (minWidthTmpBufOptUnionSelector == (2).toByte()) {
                minWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for minWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            minWidthTmpBuf = (minWidthTmpBufOpt as string | double | Resource)
        }
        const minWidthTmpResult : Length | undefined = minWidthTmpBuf
        const maxWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxWidthTmpBuf : Length | undefined = undefined
        if ((maxWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let maxWidthTmpBufOpt : string | double | Resource | undefined
            if (maxWidthTmpBufOptUnionSelector == (0).toByte()) {
                maxWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (maxWidthTmpBufOptUnionSelector == (1).toByte()) {
                maxWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (maxWidthTmpBufOptUnionSelector == (2).toByte()) {
                maxWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for maxWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            maxWidthTmpBuf = (maxWidthTmpBufOpt as string | double | Resource)
        }
        const maxWidthTmpResult : Length | undefined = maxWidthTmpBuf
        const minHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let minHeightTmpBuf : Length | undefined = undefined
        if ((minHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minHeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let minHeightTmpBufOpt : string | double | Resource | undefined
            if (minHeightTmpBufOptUnionSelector == (0).toByte()) {
                minHeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (minHeightTmpBufOptUnionSelector == (1).toByte()) {
                minHeightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (minHeightTmpBufOptUnionSelector == (2).toByte()) {
                minHeightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for minHeightTmpBufOpt has to be chosen through deserialisation.')
            }
            minHeightTmpBuf = (minHeightTmpBufOpt as string | double | Resource)
        }
        const minHeightTmpResult : Length | undefined = minHeightTmpBuf
        const maxHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxHeightTmpBuf : Length | undefined = undefined
        if ((maxHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxHeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let maxHeightTmpBufOpt : string | double | Resource | undefined
            if (maxHeightTmpBufOptUnionSelector == (0).toByte()) {
                maxHeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (maxHeightTmpBufOptUnionSelector == (1).toByte()) {
                maxHeightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (maxHeightTmpBufOptUnionSelector == (2).toByte()) {
                maxHeightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for maxHeightTmpBufOpt has to be chosen through deserialisation.')
            }
            maxHeightTmpBuf = (maxHeightTmpBufOpt as string | double | Resource)
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
            } else if (valueHolderForTopTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as number
                valueSerializer.writeNumber(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
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
            } else if (valueHolderForRightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
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
            } else if (valueHolderForBottomTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
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
            } else if (valueHolderForLeftTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeOutlineWidths {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : Dimension | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBufOpt : string | number | global_resource_Resource | undefined
            if (topTmpBufOptUnionSelector == (0).toByte()) {
                topTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topTmpBufOptUnionSelector == (1).toByte()) {
                topTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (topTmpBufOptUnionSelector == (2).toByte()) {
                topTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topTmpBufOpt has to be chosen through deserialisation.')
            }
            topTmpBuf = (topTmpBufOpt as string | number | global_resource_Resource)
        }
        const topTmpResult : Dimension | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : Dimension | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBufOpt : string | number | global_resource_Resource | undefined
            if (rightTmpBufOptUnionSelector == (0).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (rightTmpBufOptUnionSelector == (1).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (rightTmpBufOptUnionSelector == (2).toByte()) {
                rightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for rightTmpBufOpt has to be chosen through deserialisation.')
            }
            rightTmpBuf = (rightTmpBufOpt as string | number | global_resource_Resource)
        }
        const rightTmpResult : Dimension | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : Dimension | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBufOpt : string | number | global_resource_Resource | undefined
            if (bottomTmpBufOptUnionSelector == (0).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomTmpBufOptUnionSelector == (1).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (bottomTmpBufOptUnionSelector == (2).toByte()) {
                bottomTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomTmpBuf = (bottomTmpBufOpt as string | number | global_resource_Resource)
        }
        const bottomTmpResult : Dimension | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leftTmpBuf : Dimension | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBufOpt : string | number | global_resource_Resource | undefined
            if (leftTmpBufOptUnionSelector == (0).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (leftTmpBufOptUnionSelector == (1).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (leftTmpBufOptUnionSelector == (2).toByte()) {
                leftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leftTmpBufOpt has to be chosen through deserialisation.')
            }
            leftTmpBuf = (leftTmpBufOpt as string | number | global_resource_Resource)
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
            } else if (valueHolderForTopTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as number
                valueSerializer.writeNumber(valueHolderForTopTmpValueForIdx1)
            } else if (valueHolderForTopTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopTmpValueForIdx2  = valueHolderForTopTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
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
            } else if (valueHolderForLeftTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLeftTmpValueForIdx2  = valueHolderForLeftTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
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
            } else if (valueHolderForBottomTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomTmpValueForIdx2  = valueHolderForBottomTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
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
            } else if (valueHolderForRightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRightTmpValueForIdx2  = valueHolderForRightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Edges {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : Dimension | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBufOpt : string | number | global_resource_Resource | undefined
            if (topTmpBufOptUnionSelector == (0).toByte()) {
                topTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topTmpBufOptUnionSelector == (1).toByte()) {
                topTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (topTmpBufOptUnionSelector == (2).toByte()) {
                topTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topTmpBufOpt has to be chosen through deserialisation.')
            }
            topTmpBuf = (topTmpBufOpt as string | number | global_resource_Resource)
        }
        const topTmpResult : Dimension | undefined = topTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leftTmpBuf : Dimension | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBufOpt : string | number | global_resource_Resource | undefined
            if (leftTmpBufOptUnionSelector == (0).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (leftTmpBufOptUnionSelector == (1).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (leftTmpBufOptUnionSelector == (2).toByte()) {
                leftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leftTmpBufOpt has to be chosen through deserialisation.')
            }
            leftTmpBuf = (leftTmpBufOpt as string | number | global_resource_Resource)
        }
        const leftTmpResult : Dimension | undefined = leftTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : Dimension | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBufOpt : string | number | global_resource_Resource | undefined
            if (bottomTmpBufOptUnionSelector == (0).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomTmpBufOptUnionSelector == (1).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (bottomTmpBufOptUnionSelector == (2).toByte()) {
                bottomTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomTmpBuf = (bottomTmpBufOpt as string | number | global_resource_Resource)
        }
        const bottomTmpResult : Dimension | undefined = bottomTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : Dimension | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBufOpt : string | number | global_resource_Resource | undefined
            if (rightTmpBufOptUnionSelector == (0).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (rightTmpBufOptUnionSelector == (1).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (rightTmpBufOptUnionSelector == (2).toByte()) {
                rightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for rightTmpBufOpt has to be chosen through deserialisation.')
            }
            rightTmpBuf = (rightTmpBufOpt as string | number | global_resource_Resource)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EdgeWidths {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : Length | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBufOpt : string | double | Resource | undefined
            if (topTmpBufOptUnionSelector == (0).toByte()) {
                topTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topTmpBufOptUnionSelector == (1).toByte()) {
                topTmpBufOpt = valueDeserializer.readFloat64()
            } else if (topTmpBufOptUnionSelector == (2).toByte()) {
                topTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topTmpBufOpt has to be chosen through deserialisation.')
            }
            topTmpBuf = (topTmpBufOpt as string | double | Resource)
        }
        const topTmpResult : Length | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : Length | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBufOpt : string | double | Resource | undefined
            if (rightTmpBufOptUnionSelector == (0).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (rightTmpBufOptUnionSelector == (1).toByte()) {
                rightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (rightTmpBufOptUnionSelector == (2).toByte()) {
                rightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for rightTmpBufOpt has to be chosen through deserialisation.')
            }
            rightTmpBuf = (rightTmpBufOpt as string | double | Resource)
        }
        const rightTmpResult : Length | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : Length | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBufOpt : string | double | Resource | undefined
            if (bottomTmpBufOptUnionSelector == (0).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomTmpBufOptUnionSelector == (1).toByte()) {
                bottomTmpBufOpt = valueDeserializer.readFloat64()
            } else if (bottomTmpBufOptUnionSelector == (2).toByte()) {
                bottomTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomTmpBuf = (bottomTmpBufOpt as string | double | Resource)
        }
        const bottomTmpResult : Length | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leftTmpBuf : Length | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBufOpt : string | double | Resource | undefined
            if (leftTmpBufOptUnionSelector == (0).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (leftTmpBufOptUnionSelector == (1).toByte()) {
                leftTmpBufOpt = valueDeserializer.readFloat64()
            } else if (leftTmpBufOptUnionSelector == (2).toByte()) {
                leftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leftTmpBufOpt has to be chosen through deserialisation.')
            }
            leftTmpBuf = (leftTmpBufOpt as string | double | Resource)
        }
        const leftTmpResult : Length | undefined = leftTmpBuf
        let value : EdgeWidths = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeWidths)
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
            if (valueHolderForStrokeColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeColorTmpValueForIdx0  = valueHolderForStrokeColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForStrokeColorTmpValueForIdx0.getOrdinal()) % (12))
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeColorTmpValueForIdx3)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MarkStyle {
        let valueDeserializer : DeserializerBase = buffer
        const strokeColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeColorTmpBuf : ResourceColor | undefined = undefined
        if ((strokeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeColorTmpBufOpt : arkui_component_enums_Color | int32 | string | Resource | undefined
            if (strokeColorTmpBufOptUnionSelector == (0).toByte()) {
                strokeColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (strokeColorTmpBufOptUnionSelector == (1).toByte()) {
                strokeColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (strokeColorTmpBufOptUnionSelector == (2).toByte()) {
                strokeColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeColorTmpBufOptUnionSelector == (3).toByte()) {
                strokeColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeColorTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeColorTmpBuf = (strokeColorTmpBufOpt as arkui_component_enums_Color | int32 | string | Resource)
        }
        const strokeColorTmpResult : ResourceColor | undefined = strokeColorTmpBuf
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf : Length | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBufOpt : string | double | Resource | undefined
            if (sizeTmpBufOptUnionSelector == (0).toByte()) {
                sizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptUnionSelector == (1).toByte()) {
                sizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (sizeTmpBufOptUnionSelector == (2).toByte()) {
                sizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOpt has to be chosen through deserialisation.')
            }
            sizeTmpBuf = (sizeTmpBufOpt as string | double | Resource)
        }
        const sizeTmpResult : Length | undefined = sizeTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf : Length | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBufOpt : string | double | Resource | undefined
            if (strokeWidthTmpBufOptUnionSelector == (0).toByte()) {
                strokeWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBufOptUnionSelector == (1).toByte()) {
                strokeWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (strokeWidthTmpBufOptUnionSelector == (2).toByte()) {
                strokeWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeWidthTmpBuf = (strokeWidthTmpBufOpt as string | double | Resource)
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
            } else if (valueHolderForTopLeftTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopLeftTmpValueForIdx2  = valueHolderForTopLeftTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopLeftTmpValueForIdx2)
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
            } else if (valueHolderForTopRightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForTopRightTmpValueForIdx2  = valueHolderForTopRightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopRightTmpValueForIdx2)
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
            } else if (valueHolderForBottomLeftTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomLeftTmpValueForIdx2  = valueHolderForBottomLeftTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomLeftTmpValueForIdx2)
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
            } else if (valueHolderForBottomRightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBottomRightTmpValueForIdx2  = valueHolderForBottomRightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomRightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OutlineRadiuses {
        let valueDeserializer : DeserializerBase = buffer
        const topLeftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topLeftTmpBuf : Dimension | undefined = undefined
        if ((topLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topLeftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topLeftTmpBufOpt : string | number | global_resource_Resource | undefined
            if (topLeftTmpBufOptUnionSelector == (0).toByte()) {
                topLeftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topLeftTmpBufOptUnionSelector == (1).toByte()) {
                topLeftTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (topLeftTmpBufOptUnionSelector == (2).toByte()) {
                topLeftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topLeftTmpBufOpt has to be chosen through deserialisation.')
            }
            topLeftTmpBuf = (topLeftTmpBufOpt as string | number | global_resource_Resource)
        }
        const topLeftTmpResult : Dimension | undefined = topLeftTmpBuf
        const topRightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topRightTmpBuf : Dimension | undefined = undefined
        if ((topRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topRightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topRightTmpBufOpt : string | number | global_resource_Resource | undefined
            if (topRightTmpBufOptUnionSelector == (0).toByte()) {
                topRightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topRightTmpBufOptUnionSelector == (1).toByte()) {
                topRightTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (topRightTmpBufOptUnionSelector == (2).toByte()) {
                topRightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topRightTmpBufOpt has to be chosen through deserialisation.')
            }
            topRightTmpBuf = (topRightTmpBufOpt as string | number | global_resource_Resource)
        }
        const topRightTmpResult : Dimension | undefined = topRightTmpBuf
        const bottomLeftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomLeftTmpBuf : Dimension | undefined = undefined
        if ((bottomLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomLeftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomLeftTmpBufOpt : string | number | global_resource_Resource | undefined
            if (bottomLeftTmpBufOptUnionSelector == (0).toByte()) {
                bottomLeftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomLeftTmpBufOptUnionSelector == (1).toByte()) {
                bottomLeftTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (bottomLeftTmpBufOptUnionSelector == (2).toByte()) {
                bottomLeftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomLeftTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomLeftTmpBuf = (bottomLeftTmpBufOpt as string | number | global_resource_Resource)
        }
        const bottomLeftTmpResult : Dimension | undefined = bottomLeftTmpBuf
        const bottomRightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomRightTmpBuf : Dimension | undefined = undefined
        if ((bottomRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomRightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomRightTmpBufOpt : string | number | global_resource_Resource | undefined
            if (bottomRightTmpBufOptUnionSelector == (0).toByte()) {
                bottomRightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomRightTmpBufOptUnionSelector == (1).toByte()) {
                bottomRightTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (bottomRightTmpBufOptUnionSelector == (2).toByte()) {
                bottomRightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomRightTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomRightTmpBuf = (bottomRightTmpBufOpt as string | number | global_resource_Resource)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTopTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRightTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBottomTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLeftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Padding {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf : Length | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBufOpt : string | double | Resource | undefined
            if (topTmpBufOptUnionSelector == (0).toByte()) {
                topTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (topTmpBufOptUnionSelector == (1).toByte()) {
                topTmpBufOpt = valueDeserializer.readFloat64()
            } else if (topTmpBufOptUnionSelector == (2).toByte()) {
                topTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for topTmpBufOpt has to be chosen through deserialisation.')
            }
            topTmpBuf = (topTmpBufOpt as string | double | Resource)
        }
        const topTmpResult : Length | undefined = topTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf : Length | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let rightTmpBufOpt : string | double | Resource | undefined
            if (rightTmpBufOptUnionSelector == (0).toByte()) {
                rightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (rightTmpBufOptUnionSelector == (1).toByte()) {
                rightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (rightTmpBufOptUnionSelector == (2).toByte()) {
                rightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for rightTmpBufOpt has to be chosen through deserialisation.')
            }
            rightTmpBuf = (rightTmpBufOpt as string | double | Resource)
        }
        const rightTmpResult : Length | undefined = rightTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf : Length | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bottomTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let bottomTmpBufOpt : string | double | Resource | undefined
            if (bottomTmpBufOptUnionSelector == (0).toByte()) {
                bottomTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (bottomTmpBufOptUnionSelector == (1).toByte()) {
                bottomTmpBufOpt = valueDeserializer.readFloat64()
            } else if (bottomTmpBufOptUnionSelector == (2).toByte()) {
                bottomTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for bottomTmpBufOpt has to be chosen through deserialisation.')
            }
            bottomTmpBuf = (bottomTmpBufOpt as string | double | Resource)
        }
        const bottomTmpResult : Length | undefined = bottomTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leftTmpBuf : Length | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBufOpt : string | double | Resource | undefined
            if (leftTmpBufOptUnionSelector == (0).toByte()) {
                leftTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (leftTmpBufOptUnionSelector == (1).toByte()) {
                leftTmpBufOpt = valueDeserializer.readFloat64()
            } else if (leftTmpBufOptUnionSelector == (2).toByte()) {
                leftTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leftTmpBufOpt has to be chosen through deserialisation.')
            }
            leftTmpBuf = (leftTmpBufOpt as string | double | Resource)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForXTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForYTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Position {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xTmpBuf : Length | undefined = undefined
        if ((xTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xTmpBufOpt : string | double | Resource | undefined
            if (xTmpBufOptUnionSelector == (0).toByte()) {
                xTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (xTmpBufOptUnionSelector == (1).toByte()) {
                xTmpBufOpt = valueDeserializer.readFloat64()
            } else if (xTmpBufOptUnionSelector == (2).toByte()) {
                xTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for xTmpBufOpt has to be chosen through deserialisation.')
            }
            xTmpBuf = (xTmpBufOpt as string | double | Resource)
        }
        const xTmpResult : Length | undefined = xTmpBuf
        const yTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let yTmpBuf : Length | undefined = undefined
        if ((yTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let yTmpBufOpt : string | double | Resource | undefined
            if (yTmpBufOptUnionSelector == (0).toByte()) {
                yTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (yTmpBufOptUnionSelector == (1).toByte()) {
                yTmpBufOpt = valueDeserializer.readFloat64()
            } else if (yTmpBufOptUnionSelector == (2).toByte()) {
                yTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for yTmpBufOpt has to be chosen through deserialisation.')
            }
            yTmpBuf = (yTmpBufOpt as string | double | Resource)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
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
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SizeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : string | double | Resource | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (widthTmpBufOptUnionSelector == (2).toByte()) {
                widthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as string | double | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : Length | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : string | double | Resource | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (heightTmpBufOptUnionSelector == (2).toByte()) {
                heightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as string | double | Resource)
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
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthForIdx2)
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
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForHeightForIdx2)
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
        if (widthTmpBufUnionSelector == (0).toByte()) {
            widthTmpBuf = (valueDeserializer.readString() as string)
        } else if (widthTmpBufUnionSelector == (1).toByte()) {
            widthTmpBuf = valueDeserializer.readFloat64()
        } else if (widthTmpBufUnionSelector == (2).toByte()) {
            widthTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for widthTmpBuf has to be chosen through deserialisation.')
        }
        const widthTmpResult : Length = (widthTmpBuf as string | double | Resource)
        const heightTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let heightTmpBuf : string | double | Resource | undefined
        if (heightTmpBufUnionSelector == (0).toByte()) {
            heightTmpBuf = (valueDeserializer.readString() as string)
        } else if (heightTmpBufUnionSelector == (1).toByte()) {
            heightTmpBuf = valueDeserializer.readFloat64()
        } else if (heightTmpBufUnionSelector == (2).toByte()) {
            heightTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for heightTmpBuf has to be chosen through deserialisation.')
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
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx1ForIdx2)
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
                if (valueHolderForColorTmpValueForIdx1 instanceof arkui_component_enums_Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx0  = valueHolderForColorTmpValueForIdx1 as arkui_component_enums_Color
                    valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx1ForIdx0.getOrdinal()) % (12))
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
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx1ForIdx3)
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
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1ForIdx2)
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
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForDashGapTmpValueForIdx1)
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
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForDashWidthTmpValueForIdx1)
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
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : EdgeWidths | Length | LocalizedEdgeWidths | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : EdgeWidths | Length | LocalizedEdgeWidths | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = EdgeWidths_serializer.read(valueDeserializer)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                const widthTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let widthTmpBufOptBufU : string | double | Resource | undefined
                if (widthTmpBufOptBufUUnionSelector == (0).toByte()) {
                    widthTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (widthTmpBufOptBufUUnionSelector == (1).toByte()) {
                    widthTmpBufOptBufU = valueDeserializer.readFloat64()
                } else if (widthTmpBufOptBufUUnionSelector == (2).toByte()) {
                    widthTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for widthTmpBufOptBufU has to be chosen through deserialisation.')
                }
                widthTmpBufOpt = (widthTmpBufOptBufU as string | double | Resource)
            } else if (widthTmpBufOptUnionSelector == (2).toByte()) {
                widthTmpBufOpt = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as EdgeWidths | Length | LocalizedEdgeWidths)
        }
        const widthTmpResult : EdgeWidths | Length | LocalizedEdgeWidths | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = EdgeColors_serializer.read(valueDeserializer)
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                const colorTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBufOptBufU : arkui_component_enums_Color | int32 | string | Resource | undefined
                if (colorTmpBufOptBufUUnionSelector == (0).toByte()) {
                    colorTmpBufOptBufU = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                } else if (colorTmpBufOptBufUUnionSelector == (1).toByte()) {
                    colorTmpBufOptBufU = valueDeserializer.readInt32()
                } else if (colorTmpBufOptBufUUnionSelector == (2).toByte()) {
                    colorTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (colorTmpBufOptBufUUnionSelector == (3).toByte()) {
                    colorTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for colorTmpBufOptBufU has to be chosen through deserialisation.')
                }
                colorTmpBufOpt = (colorTmpBufOptBufU as arkui_component_enums_Color | int32 | string | Resource)
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as EdgeColors | ResourceColor | LocalizedEdgeColors)
        }
        const colorTmpResult : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = colorTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBufOpt : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined
            if (radiusTmpBufOptUnionSelector == (0).toByte()) {
                radiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (radiusTmpBufOptUnionSelector == (1).toByte()) {
                const radiusTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBufOptBufU : string | double | Resource | undefined
                if (radiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    radiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    radiusTmpBufOptBufU = valueDeserializer.readFloat64()
                } else if (radiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    radiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for radiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                radiusTmpBufOpt = (radiusTmpBufOptBufU as string | double | Resource)
            } else if (radiusTmpBufOptUnionSelector == (2).toByte()) {
                radiusTmpBufOpt = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for radiusTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusTmpBuf = (radiusTmpBufOpt as BorderRadiuses | Length | LocalizedBorderRadiuses)
        }
        const radiusTmpResult : BorderRadiuses | Length | LocalizedBorderRadiuses | undefined = radiusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : EdgeStyles | BorderStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const styleTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let styleTmpBufOpt : EdgeStyles | BorderStyle | undefined
            if (styleTmpBufOptUnionSelector == (0).toByte()) {
                styleTmpBufOpt = EdgeStyles_serializer.read(valueDeserializer)
            } else if (styleTmpBufOptUnionSelector == (1).toByte()) {
                styleTmpBufOpt = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for styleTmpBufOpt has to be chosen through deserialisation.')
            }
            styleTmpBuf = (styleTmpBufOpt as EdgeStyles | BorderStyle)
        }
        const styleTmpResult : EdgeStyles | BorderStyle | undefined = styleTmpBuf
        const dashGapTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dashGapTmpBuf : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = undefined
        if ((dashGapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const dashGapTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let dashGapTmpBufOpt : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
            if (dashGapTmpBufOptUnionSelector == (0).toByte()) {
                dashGapTmpBufOpt = EdgeWidths_serializer.read(valueDeserializer)
            } else if (dashGapTmpBufOptUnionSelector == (1).toByte()) {
                dashGapTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (dashGapTmpBufOptUnionSelector == (2).toByte()) {
                dashGapTmpBufOpt = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for dashGapTmpBufOpt has to be chosen through deserialisation.')
            }
            dashGapTmpBuf = (dashGapTmpBufOpt as EdgeWidths | LengthMetrics | LocalizedEdgeWidths)
        }
        const dashGapTmpResult : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = dashGapTmpBuf
        const dashWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dashWidthTmpBuf : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = undefined
        if ((dashWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const dashWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let dashWidthTmpBufOpt : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined
            if (dashWidthTmpBufOptUnionSelector == (0).toByte()) {
                dashWidthTmpBufOpt = EdgeWidths_serializer.read(valueDeserializer)
            } else if (dashWidthTmpBufOptUnionSelector == (1).toByte()) {
                dashWidthTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (dashWidthTmpBufOptUnionSelector == (2).toByte()) {
                dashWidthTmpBufOpt = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for dashWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            dashWidthTmpBuf = (dashWidthTmpBufOpt as EdgeWidths | LengthMetrics | LocalizedEdgeWidths)
        }
        const dashWidthTmpResult : EdgeWidths | LengthMetrics | LocalizedEdgeWidths | undefined = dashWidthTmpBuf
        const showInForegroundTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
                } else if (valueHolderForWidthTmpValueForIdx1 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForWidthTmpValueForIdx1ForIdx2  = valueHolderForWidthTmpValueForIdx1 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx1ForIdx2)
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
                if (valueHolderForColorTmpValueForIdx1 instanceof arkui_component_enums_Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorTmpValueForIdx1ForIdx0  = valueHolderForColorTmpValueForIdx1 as arkui_component_enums_Color
                    valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx1ForIdx0.getOrdinal()) % (12))
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
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx1ForIdx3)
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
                } else if (valueHolderForRadiusTmpValueForIdx1 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForRadiusTmpValueForIdx1ForIdx2  = valueHolderForRadiusTmpValueForIdx1 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1ForIdx2)
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
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : EdgeOutlineWidths | Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : EdgeOutlineWidths | Dimension | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = EdgeOutlineWidths_serializer.read(valueDeserializer)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                const widthTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let widthTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (widthTmpBufOptBufUUnionSelector == (0).toByte()) {
                    widthTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (widthTmpBufOptBufUUnionSelector == (1).toByte()) {
                    widthTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (widthTmpBufOptBufUUnionSelector == (2).toByte()) {
                    widthTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for widthTmpBufOptBufU has to be chosen through deserialisation.')
                }
                widthTmpBufOpt = (widthTmpBufOptBufU as string | number | global_resource_Resource)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as EdgeOutlineWidths | Dimension)
        }
        const widthTmpResult : EdgeOutlineWidths | Dimension | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = EdgeColors_serializer.read(valueDeserializer)
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                const colorTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBufOptBufU : arkui_component_enums_Color | int32 | string | Resource | undefined
                if (colorTmpBufOptBufUUnionSelector == (0).toByte()) {
                    colorTmpBufOptBufU = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                } else if (colorTmpBufOptBufUUnionSelector == (1).toByte()) {
                    colorTmpBufOptBufU = valueDeserializer.readInt32()
                } else if (colorTmpBufOptBufUUnionSelector == (2).toByte()) {
                    colorTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (colorTmpBufOptBufUUnionSelector == (3).toByte()) {
                    colorTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for colorTmpBufOptBufU has to be chosen through deserialisation.')
                }
                colorTmpBufOpt = (colorTmpBufOptBufU as arkui_component_enums_Color | int32 | string | Resource)
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as EdgeColors | ResourceColor | LocalizedEdgeColors)
        }
        const colorTmpResult : EdgeColors | ResourceColor | LocalizedEdgeColors | undefined = colorTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : OutlineRadiuses | Dimension | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBufOpt : OutlineRadiuses | Dimension | undefined
            if (radiusTmpBufOptUnionSelector == (0).toByte()) {
                radiusTmpBufOpt = OutlineRadiuses_serializer.read(valueDeserializer)
            } else if (radiusTmpBufOptUnionSelector == (1).toByte()) {
                const radiusTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (radiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    radiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    radiusTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (radiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    radiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for radiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                radiusTmpBufOpt = (radiusTmpBufOptBufU as string | number | global_resource_Resource)
            } else {
                throw new Error('One of the branches for radiusTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusTmpBuf = (radiusTmpBufOpt as OutlineRadiuses | Dimension)
        }
        const radiusTmpResult : OutlineRadiuses | Dimension | undefined = radiusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : EdgeOutlineStyles | OutlineStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const styleTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let styleTmpBufOpt : EdgeOutlineStyles | OutlineStyle | undefined
            if (styleTmpBufOptUnionSelector == (0).toByte()) {
                styleTmpBufOpt = EdgeOutlineStyles_serializer.read(valueDeserializer)
            } else if (styleTmpBufOptUnionSelector == (1).toByte()) {
                styleTmpBufOpt = OutlineStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for styleTmpBufOpt has to be chosen through deserialisation.')
            }
            styleTmpBuf = (styleTmpBufOpt as EdgeOutlineStyles | OutlineStyle)
        }
        const styleTmpResult : EdgeOutlineStyles | OutlineStyle | undefined = styleTmpBuf
        let value : OutlineOptions = ({width: widthTmpResult, color: colorTmpResult, radius: radiusTmpResult, style: styleTmpResult} as OutlineOptions)
        return value
    }
}

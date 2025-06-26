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
import { Resource_serializer, Resource } from "./resource"
import { SizeOptions_serializer, Length, SizeOptions, Position_serializer, Position, ResourceColor } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Color, FontStyle, FontWeight, TextOverflow, TextCase } from "./enums"
import { image } from "./ohos.multimedia.image"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { text } from "./ohos.graphics.text"
export class BaseShapeInternal {
    public static fromPtr(ptr: KPointer): BaseShape {
        return new BaseShape(ptr)
    }
}
export class BaseShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BaseShape.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_ctor()
        return retval
    }
    constructor() {
        this(BaseShape.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseShape_getFinalizer()
    }
    public width(width: Length): BaseShape {
        const width_casted = width as (Length)
        return this.width_serialize(width_casted)
    }
    public height(height: Length): BaseShape {
        const height_casted = height as (Length)
        return this.height_serialize(height_casted)
    }
    public size(size: SizeOptions): BaseShape {
        const size_casted = size as (SizeOptions)
        return this.size_serialize(size_casted)
    }
    private width_serialize(width: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let width_type : int32 = RuntimeType.UNDEFINED
        width_type = runtimeType(width)
        if (RuntimeType.STRING == width_type) {
            thisSerializer.writeInt8(0)
            const width_0  = width as string
            thisSerializer.writeString(width_0)
        }
        else if (RuntimeType.NUMBER == width_type) {
            thisSerializer.writeInt8(1)
            const width_1  = width as number
            thisSerializer.writeNumber(width_1)
        }
        else if (RuntimeType.OBJECT == width_type) {
            thisSerializer.writeInt8(2)
            const width_2  = width as Resource
            Resource_serializer.write(thisSerializer, width_2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let height_type : int32 = RuntimeType.UNDEFINED
        height_type = runtimeType(height)
        if (RuntimeType.STRING == height_type) {
            thisSerializer.writeInt8(0)
            const height_0  = height as string
            thisSerializer.writeString(height_0)
        }
        else if (RuntimeType.NUMBER == height_type) {
            thisSerializer.writeInt8(1)
            const height_1  = height as number
            thisSerializer.writeNumber(height_1)
        }
        else if (RuntimeType.OBJECT == height_type) {
            thisSerializer.writeInt8(2)
            const height_2  = height as Resource
            Resource_serializer.write(thisSerializer, height_2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SizeOptions_serializer.write(thisSerializer, size)
        const retval  = ArkUIGeneratedNativeModule._BaseShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
}
export class CommonShapeInternal {
    public static fromPtr(ptr: KPointer): CommonShape {
        return new CommonShape(ptr)
    }
}
export class CommonShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CommonShape.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CommonShape_ctor()
        return retval
    }
    constructor() {
        this(CommonShape.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CommonShape_getFinalizer()
    }
    public offset(offset: Position): CommonShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): CommonShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): CommonShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    private offset_serialize(offset: Position): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8(0)
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1)
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2)
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3)
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._CommonShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
}
export class GlobalScope_ohos_arkui_componentSnapshot {
    public static get(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
        const id_casted = id as (string)
        const callback_casted = callback as (((result: image.PixelMap) => void))
        const options_casted = options as (SnapshotOptions | undefined)
        GlobalScope_ohos_arkui_componentSnapshot.get_serialize(id_casted, callback_casted, options_casted)
        return
    }
    private static get_serialize(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            SnapshotOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_componentSnapshot_get(id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class GlobalScope_ohos_arkui_performanceMonitor {
    public static begin(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const scene_casted = scene as (string)
        const startInputType_casted = startInputType as (PerfMonitorActionType)
        const note_casted = note as (string | undefined)
        GlobalScope_ohos_arkui_performanceMonitor.begin_serialize(scene_casted, startInputType_casted, note_casted)
        return
    }
    public static end(scene: string): void {
        const scene_casted = scene as (string)
        GlobalScope_ohos_arkui_performanceMonitor.end_serialize(scene_casted)
        return
    }
    public static recordInputEventTime(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: int64): void {
        const actionType_casted = actionType as (PerfMonitorActionType)
        const sourceType_casted = sourceType as (PerfMonitorSourceType)
        const time_casted = time as (int64)
        GlobalScope_ohos_arkui_performanceMonitor.recordInputEventTime_serialize(actionType_casted, sourceType_casted, time_casted)
        return
    }
    private static begin_serialize(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let note_type : int32 = RuntimeType.UNDEFINED
        note_type = runtimeType(note)
        thisSerializer.writeInt8(note_type)
        if ((RuntimeType.UNDEFINED) != (note_type)) {
            const note_value  = note!
            thisSerializer.writeString(note_value)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_begin(scene, TypeChecker.PerfMonitorActionType_ToNumeric(startInputType), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static end_serialize(scene: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_end(scene)
    }
    private static recordInputEventTime_serialize(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: int64): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(TypeChecker.PerfMonitorActionType_ToNumeric(actionType), TypeChecker.PerfMonitorSourceType_ToNumeric(sourceType), time)
    }
}
export class GlobalScope_ohos_font {
    public static registerFont(options: FontOptions): void {
        const options_casted = options as (FontOptions)
        GlobalScope_ohos_font.registerFont_serialize(options_casted)
        return
    }
    public static getSystemFontList(): Array<string> {
        return GlobalScope_ohos_font.getSystemFontList_serialize()
    }
    public static getFontByName(fontName: string): FontInfo {
        const fontName_casted = fontName as (string)
        return GlobalScope_ohos_font.getFontByName_serialize(fontName_casted)
    }
    private static registerFont_serialize(options: FontOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FontOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GlobalScope_ohos_font_registerFont(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getSystemFontList_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getSystemFontList()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private static getFontByName_serialize(fontName: string): FontInfo {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getFontByName(fontName)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : FontInfo = FontInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export class GlobalScope_ohos_measure_utils {
    public static measureText(options: MeasureOptions): number {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureText_serialize(options_casted)
    }
    public static measureTextSize(options: MeasureOptions): SizeOptions {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureTextSize_serialize(options_casted)
    }
    private static measureText_serialize(options: MeasureOptions): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureText(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static measureTextSize_serialize(options: MeasureOptions): SizeOptions {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureTextSize(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SizeOptions = SizeOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export interface WebHeader {
    headerKey: string;
    headerValue: string;
}
export interface SnapshotOptions {
    scale?: number;
    waitUntilRenderFinished?: boolean;
}
export enum PerfMonitorActionType {
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
}
export enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4
}
export interface FontOptions {
    familyName: string | Resource;
    familySrc: string | Resource;
}
export interface MeasureOptions {
    textContent: string | Resource;
    constraintWidth?: number | string | Resource;
    fontSize?: number | string | Resource;
    fontStyle?: number | FontStyle;
    fontWeight?: number | string | FontWeight;
    fontFamily?: string | Resource;
    letterSpacing?: number | string;
    textAlign?: text.TextAlign;
    overflow?: number | TextOverflow;
    maxLines?: number;
    lineHeight?: number | string | Resource;
    baselineOffset?: number | string;
    textCase?: number | TextCase;
    textIndent?: number | string;
    wordBreak?: text.WordBreak;
}
export interface FontInfo {
    path: string;
    postScriptName: string;
    fullName: string;
    family: string;
    subfamily: string;
    weight: number;
    width: number;
    italic: boolean;
    monoSpace: boolean;
    symbolic: boolean;
}
export interface IndicatorStyle {
    height?: Length;
    width?: Length;
    borderRadius?: Length;
    marginTop?: Length;
    color?: ResourceColor;
    selectedColor?: ResourceColor;
    left?: Length;
    top?: Length;
    right?: Length;
    bottom?: Length;
    size?: Length;
    mask?: boolean;
}
export class BaseShape_serializer {
    public static write(buffer: SerializerBase, value: BaseShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BaseShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BaseShapeInternal.fromPtr(ptr)
    }
}
export class CommonShape_serializer {
    public static write(buffer: SerializerBase, value: CommonShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CommonShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CommonShapeInternal.fromPtr(ptr)
    }
}
export class FontInfo_serializer {
    public static write(buffer: SerializerBase, value: FontInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_path  = value.path
        valueSerializer.writeString(value_path)
        const value_postScriptName  = value.postScriptName
        valueSerializer.writeString(value_postScriptName)
        const value_fullName  = value.fullName
        valueSerializer.writeString(value_fullName)
        const value_family  = value.family
        valueSerializer.writeString(value_family)
        const value_subfamily  = value.subfamily
        valueSerializer.writeString(value_subfamily)
        const value_weight  = value.weight
        valueSerializer.writeNumber(value_weight)
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_italic  = value.italic
        valueSerializer.writeBoolean(value_italic)
        const value_monoSpace  = value.monoSpace
        valueSerializer.writeBoolean(value_monoSpace)
        const value_symbolic  = value.symbolic
        valueSerializer.writeBoolean(value_symbolic)
    }
    public static read(buffer: DeserializerBase): FontInfo {
        let valueDeserializer : DeserializerBase = buffer
        const path_result : string = (valueDeserializer.readString() as string)
        const postScriptName_result : string = (valueDeserializer.readString() as string)
        const fullName_result : string = (valueDeserializer.readString() as string)
        const family_result : string = (valueDeserializer.readString() as string)
        const subfamily_result : string = (valueDeserializer.readString() as string)
        const weight_result : number = (valueDeserializer.readNumber() as number)
        const width_result : number = (valueDeserializer.readNumber() as number)
        const italic_result : boolean = valueDeserializer.readBoolean()
        const monoSpace_result : boolean = valueDeserializer.readBoolean()
        const symbolic_result : boolean = valueDeserializer.readBoolean()
        let value : FontInfo = ({path: path_result, postScriptName: postScriptName_result, fullName: fullName_result, family: family_result, subfamily: subfamily_result, weight: weight_result, width: width_result, italic: italic_result, monoSpace: monoSpace_result, symbolic: symbolic_result} as FontInfo)
        return value
    }
}
export class SnapshotOptions_serializer {
    public static write(buffer: SerializerBase, value: SnapshotOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_scale  = value.scale
        let value_scale_type : int32 = RuntimeType.UNDEFINED
        value_scale_type = runtimeType(value_scale)
        valueSerializer.writeInt8(value_scale_type)
        if ((RuntimeType.UNDEFINED) != (value_scale_type)) {
            const value_scale_value  = value_scale!
            valueSerializer.writeNumber(value_scale_value)
        }
        const value_waitUntilRenderFinished  = value.waitUntilRenderFinished
        let value_waitUntilRenderFinished_type : int32 = RuntimeType.UNDEFINED
        value_waitUntilRenderFinished_type = runtimeType(value_waitUntilRenderFinished)
        valueSerializer.writeInt8(value_waitUntilRenderFinished_type)
        if ((RuntimeType.UNDEFINED) != (value_waitUntilRenderFinished_type)) {
            const value_waitUntilRenderFinished_value  = value_waitUntilRenderFinished!
            valueSerializer.writeBoolean(value_waitUntilRenderFinished_value)
        }
    }
    public static read(buffer: DeserializerBase): SnapshotOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scale_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let scale_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (scale_buf_runtimeType))
        {
            scale_buf = (valueDeserializer.readNumber() as number)
        }
        const scale_result : number | undefined = scale_buf
        const waitUntilRenderFinished_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let waitUntilRenderFinished_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (waitUntilRenderFinished_buf_runtimeType))
        {
            waitUntilRenderFinished_buf = valueDeserializer.readBoolean()
        }
        const waitUntilRenderFinished_result : boolean | undefined = waitUntilRenderFinished_buf
        let value : SnapshotOptions = ({scale: scale_result, waitUntilRenderFinished: waitUntilRenderFinished_result} as SnapshotOptions)
        return value
    }
}
export class FontOptions_serializer {
    public static write(buffer: SerializerBase, value: FontOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_familyName  = value.familyName
        let value_familyName_type : int32 = RuntimeType.UNDEFINED
        value_familyName_type = runtimeType(value_familyName)
        if (RuntimeType.STRING == value_familyName_type) {
            valueSerializer.writeInt8(0)
            const value_familyName_0  = value_familyName as string
            valueSerializer.writeString(value_familyName_0)
        }
        else if (RuntimeType.OBJECT == value_familyName_type) {
            valueSerializer.writeInt8(1)
            const value_familyName_1  = value_familyName as Resource
            Resource_serializer.write(valueSerializer, value_familyName_1)
        }
        const value_familySrc  = value.familySrc
        let value_familySrc_type : int32 = RuntimeType.UNDEFINED
        value_familySrc_type = runtimeType(value_familySrc)
        if (RuntimeType.STRING == value_familySrc_type) {
            valueSerializer.writeInt8(0)
            const value_familySrc_0  = value_familySrc as string
            valueSerializer.writeString(value_familySrc_0)
        }
        else if (RuntimeType.OBJECT == value_familySrc_type) {
            valueSerializer.writeInt8(1)
            const value_familySrc_1  = value_familySrc as Resource
            Resource_serializer.write(valueSerializer, value_familySrc_1)
        }
    }
    public static read(buffer: DeserializerBase): FontOptions {
        let valueDeserializer : DeserializerBase = buffer
        const familyName_buf_selector : int32 = valueDeserializer.readInt8()
        let familyName_buf : string | Resource | undefined
        if (familyName_buf_selector == 0) {
            familyName_buf = (valueDeserializer.readString() as string)
        }
        else if (familyName_buf_selector == 1) {
            familyName_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for familyName_buf has to be chosen through deserialisation.")
        }
        const familyName_result : string | Resource = (familyName_buf as string | Resource)
        const familySrc_buf_selector : int32 = valueDeserializer.readInt8()
        let familySrc_buf : string | Resource | undefined
        if (familySrc_buf_selector == 0) {
            familySrc_buf = (valueDeserializer.readString() as string)
        }
        else if (familySrc_buf_selector == 1) {
            familySrc_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for familySrc_buf has to be chosen through deserialisation.")
        }
        const familySrc_result : string | Resource = (familySrc_buf as string | Resource)
        let value : FontOptions = ({familyName: familyName_result, familySrc: familySrc_result} as FontOptions)
        return value
    }
}
export class MeasureOptions_serializer {
    public static write(buffer: SerializerBase, value: MeasureOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_textContent  = value.textContent
        let value_textContent_type : int32 = RuntimeType.UNDEFINED
        value_textContent_type = runtimeType(value_textContent)
        if (RuntimeType.STRING == value_textContent_type) {
            valueSerializer.writeInt8(0)
            const value_textContent_0  = value_textContent as string
            valueSerializer.writeString(value_textContent_0)
        }
        else if (RuntimeType.OBJECT == value_textContent_type) {
            valueSerializer.writeInt8(1)
            const value_textContent_1  = value_textContent as Resource
            Resource_serializer.write(valueSerializer, value_textContent_1)
        }
        const value_constraintWidth  = value.constraintWidth
        let value_constraintWidth_type : int32 = RuntimeType.UNDEFINED
        value_constraintWidth_type = runtimeType(value_constraintWidth)
        valueSerializer.writeInt8(value_constraintWidth_type)
        if ((RuntimeType.UNDEFINED) != (value_constraintWidth_type)) {
            const value_constraintWidth_value  = value_constraintWidth!
            let value_constraintWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_constraintWidth_value_type = runtimeType(value_constraintWidth_value)
            if (RuntimeType.NUMBER == value_constraintWidth_value_type) {
                valueSerializer.writeInt8(0)
                const value_constraintWidth_value_0  = value_constraintWidth_value as number
                valueSerializer.writeNumber(value_constraintWidth_value_0)
            }
            else if (RuntimeType.STRING == value_constraintWidth_value_type) {
                valueSerializer.writeInt8(1)
                const value_constraintWidth_value_1  = value_constraintWidth_value as string
                valueSerializer.writeString(value_constraintWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_constraintWidth_value_type) {
                valueSerializer.writeInt8(2)
                const value_constraintWidth_value_2  = value_constraintWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_constraintWidth_value_2)
            }
        }
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8(value_fontSize_type)
        if ((RuntimeType.UNDEFINED) != (value_fontSize_type)) {
            const value_fontSize_value  = value_fontSize!
            let value_fontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_fontSize_value_type = runtimeType(value_fontSize_value)
            if (RuntimeType.NUMBER == value_fontSize_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontSize_value_0  = value_fontSize_value as number
                valueSerializer.writeNumber(value_fontSize_value_0)
            }
            else if (RuntimeType.STRING == value_fontSize_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontSize_value_1  = value_fontSize_value as string
                valueSerializer.writeString(value_fontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_fontSize_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontSize_value_2  = value_fontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_fontSize_value_2)
            }
        }
        const value_fontStyle  = value.fontStyle
        let value_fontStyle_type : int32 = RuntimeType.UNDEFINED
        value_fontStyle_type = runtimeType(value_fontStyle)
        valueSerializer.writeInt8(value_fontStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_fontStyle_type)) {
            const value_fontStyle_value  = value_fontStyle!
            let value_fontStyle_value_type : int32 = RuntimeType.UNDEFINED
            value_fontStyle_value_type = runtimeType(value_fontStyle_value)
            if (RuntimeType.NUMBER == value_fontStyle_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontStyle_value_0  = value_fontStyle_value as number
                valueSerializer.writeNumber(value_fontStyle_value_0)
            }
            else if (TypeChecker.isFontStyle(value_fontStyle_value)) {
                valueSerializer.writeInt8(1)
                const value_fontStyle_value_1  = value_fontStyle_value as FontStyle
                valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_fontStyle_value_1))
            }
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8(value_fontWeight_type)
        if ((RuntimeType.UNDEFINED) != (value_fontWeight_type)) {
            const value_fontWeight_value  = value_fontWeight!
            let value_fontWeight_value_type : int32 = RuntimeType.UNDEFINED
            value_fontWeight_value_type = runtimeType(value_fontWeight_value)
            if (RuntimeType.NUMBER == value_fontWeight_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontWeight_value_0  = value_fontWeight_value as number
                valueSerializer.writeNumber(value_fontWeight_value_0)
            }
            else if (RuntimeType.STRING == value_fontWeight_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontWeight_value_1  = value_fontWeight_value as string
                valueSerializer.writeString(value_fontWeight_value_1)
            }
            else if (TypeChecker.isFontWeight(value_fontWeight_value)) {
                valueSerializer.writeInt8(2)
                const value_fontWeight_value_2  = value_fontWeight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_fontWeight_value_2))
            }
        }
        const value_fontFamily  = value.fontFamily
        let value_fontFamily_type : int32 = RuntimeType.UNDEFINED
        value_fontFamily_type = runtimeType(value_fontFamily)
        valueSerializer.writeInt8(value_fontFamily_type)
        if ((RuntimeType.UNDEFINED) != (value_fontFamily_type)) {
            const value_fontFamily_value  = value_fontFamily!
            let value_fontFamily_value_type : int32 = RuntimeType.UNDEFINED
            value_fontFamily_value_type = runtimeType(value_fontFamily_value)
            if (RuntimeType.STRING == value_fontFamily_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontFamily_value_0  = value_fontFamily_value as string
                valueSerializer.writeString(value_fontFamily_value_0)
            }
            else if (RuntimeType.OBJECT == value_fontFamily_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontFamily_value_1  = value_fontFamily_value as Resource
                Resource_serializer.write(valueSerializer, value_fontFamily_value_1)
            }
        }
        const value_letterSpacing  = value.letterSpacing
        let value_letterSpacing_type : int32 = RuntimeType.UNDEFINED
        value_letterSpacing_type = runtimeType(value_letterSpacing)
        valueSerializer.writeInt8(value_letterSpacing_type)
        if ((RuntimeType.UNDEFINED) != (value_letterSpacing_type)) {
            const value_letterSpacing_value  = value_letterSpacing!
            let value_letterSpacing_value_type : int32 = RuntimeType.UNDEFINED
            value_letterSpacing_value_type = runtimeType(value_letterSpacing_value)
            if (RuntimeType.NUMBER == value_letterSpacing_value_type) {
                valueSerializer.writeInt8(0)
                const value_letterSpacing_value_0  = value_letterSpacing_value as number
                valueSerializer.writeNumber(value_letterSpacing_value_0)
            }
            else if (RuntimeType.STRING == value_letterSpacing_value_type) {
                valueSerializer.writeInt8(1)
                const value_letterSpacing_value_1  = value_letterSpacing_value as string
                valueSerializer.writeString(value_letterSpacing_value_1)
            }
        }
        const value_textAlign  = value.textAlign
        let value_textAlign_type : int32 = RuntimeType.UNDEFINED
        value_textAlign_type = runtimeType(value_textAlign)
        valueSerializer.writeInt8(value_textAlign_type)
        if ((RuntimeType.UNDEFINED) != (value_textAlign_type)) {
            const value_textAlign_value  = (value_textAlign as text.TextAlign)
            valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(value_textAlign_value))
        }
        const value_overflow  = value.overflow
        let value_overflow_type : int32 = RuntimeType.UNDEFINED
        value_overflow_type = runtimeType(value_overflow)
        valueSerializer.writeInt8(value_overflow_type)
        if ((RuntimeType.UNDEFINED) != (value_overflow_type)) {
            const value_overflow_value  = value_overflow!
            let value_overflow_value_type : int32 = RuntimeType.UNDEFINED
            value_overflow_value_type = runtimeType(value_overflow_value)
            if (RuntimeType.NUMBER == value_overflow_value_type) {
                valueSerializer.writeInt8(0)
                const value_overflow_value_0  = value_overflow_value as number
                valueSerializer.writeNumber(value_overflow_value_0)
            }
            else if (TypeChecker.isTextOverflow(value_overflow_value)) {
                valueSerializer.writeInt8(1)
                const value_overflow_value_1  = value_overflow_value as TextOverflow
                valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow_value_1))
            }
        }
        const value_maxLines  = value.maxLines
        let value_maxLines_type : int32 = RuntimeType.UNDEFINED
        value_maxLines_type = runtimeType(value_maxLines)
        valueSerializer.writeInt8(value_maxLines_type)
        if ((RuntimeType.UNDEFINED) != (value_maxLines_type)) {
            const value_maxLines_value  = value_maxLines!
            valueSerializer.writeNumber(value_maxLines_value)
        }
        const value_lineHeight  = value.lineHeight
        let value_lineHeight_type : int32 = RuntimeType.UNDEFINED
        value_lineHeight_type = runtimeType(value_lineHeight)
        valueSerializer.writeInt8(value_lineHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_lineHeight_type)) {
            const value_lineHeight_value  = value_lineHeight!
            let value_lineHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_lineHeight_value_type = runtimeType(value_lineHeight_value)
            if (RuntimeType.NUMBER == value_lineHeight_value_type) {
                valueSerializer.writeInt8(0)
                const value_lineHeight_value_0  = value_lineHeight_value as number
                valueSerializer.writeNumber(value_lineHeight_value_0)
            }
            else if (RuntimeType.STRING == value_lineHeight_value_type) {
                valueSerializer.writeInt8(1)
                const value_lineHeight_value_1  = value_lineHeight_value as string
                valueSerializer.writeString(value_lineHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value_lineHeight_value_type) {
                valueSerializer.writeInt8(2)
                const value_lineHeight_value_2  = value_lineHeight_value as Resource
                Resource_serializer.write(valueSerializer, value_lineHeight_value_2)
            }
        }
        const value_baselineOffset  = value.baselineOffset
        let value_baselineOffset_type : int32 = RuntimeType.UNDEFINED
        value_baselineOffset_type = runtimeType(value_baselineOffset)
        valueSerializer.writeInt8(value_baselineOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_baselineOffset_type)) {
            const value_baselineOffset_value  = value_baselineOffset!
            let value_baselineOffset_value_type : int32 = RuntimeType.UNDEFINED
            value_baselineOffset_value_type = runtimeType(value_baselineOffset_value)
            if (RuntimeType.NUMBER == value_baselineOffset_value_type) {
                valueSerializer.writeInt8(0)
                const value_baselineOffset_value_0  = value_baselineOffset_value as number
                valueSerializer.writeNumber(value_baselineOffset_value_0)
            }
            else if (RuntimeType.STRING == value_baselineOffset_value_type) {
                valueSerializer.writeInt8(1)
                const value_baselineOffset_value_1  = value_baselineOffset_value as string
                valueSerializer.writeString(value_baselineOffset_value_1)
            }
        }
        const value_textCase  = value.textCase
        let value_textCase_type : int32 = RuntimeType.UNDEFINED
        value_textCase_type = runtimeType(value_textCase)
        valueSerializer.writeInt8(value_textCase_type)
        if ((RuntimeType.UNDEFINED) != (value_textCase_type)) {
            const value_textCase_value  = value_textCase!
            let value_textCase_value_type : int32 = RuntimeType.UNDEFINED
            value_textCase_value_type = runtimeType(value_textCase_value)
            if (RuntimeType.NUMBER == value_textCase_value_type) {
                valueSerializer.writeInt8(0)
                const value_textCase_value_0  = value_textCase_value as number
                valueSerializer.writeNumber(value_textCase_value_0)
            }
            else if (TypeChecker.isTextCase(value_textCase_value)) {
                valueSerializer.writeInt8(1)
                const value_textCase_value_1  = value_textCase_value as TextCase
                valueSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(value_textCase_value_1))
            }
        }
        const value_textIndent  = value.textIndent
        let value_textIndent_type : int32 = RuntimeType.UNDEFINED
        value_textIndent_type = runtimeType(value_textIndent)
        valueSerializer.writeInt8(value_textIndent_type)
        if ((RuntimeType.UNDEFINED) != (value_textIndent_type)) {
            const value_textIndent_value  = value_textIndent!
            let value_textIndent_value_type : int32 = RuntimeType.UNDEFINED
            value_textIndent_value_type = runtimeType(value_textIndent_value)
            if (RuntimeType.NUMBER == value_textIndent_value_type) {
                valueSerializer.writeInt8(0)
                const value_textIndent_value_0  = value_textIndent_value as number
                valueSerializer.writeNumber(value_textIndent_value_0)
            }
            else if (RuntimeType.STRING == value_textIndent_value_type) {
                valueSerializer.writeInt8(1)
                const value_textIndent_value_1  = value_textIndent_value as string
                valueSerializer.writeString(value_textIndent_value_1)
            }
        }
        const value_wordBreak  = value.wordBreak
        let value_wordBreak_type : int32 = RuntimeType.UNDEFINED
        value_wordBreak_type = runtimeType(value_wordBreak)
        valueSerializer.writeInt8(value_wordBreak_type)
        if ((RuntimeType.UNDEFINED) != (value_wordBreak_type)) {
            const value_wordBreak_value  = (value_wordBreak as text.WordBreak)
            valueSerializer.writeInt32(TypeChecker.text_WordBreak_ToNumeric(value_wordBreak_value))
        }
    }
    public static read(buffer: DeserializerBase): MeasureOptions {
        let valueDeserializer : DeserializerBase = buffer
        const textContent_buf_selector : int32 = valueDeserializer.readInt8()
        let textContent_buf : string | Resource | undefined
        if (textContent_buf_selector == 0) {
            textContent_buf = (valueDeserializer.readString() as string)
        }
        else if (textContent_buf_selector == 1) {
            textContent_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for textContent_buf has to be chosen through deserialisation.")
        }
        const textContent_result : string | Resource = (textContent_buf as string | Resource)
        const constraintWidth_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let constraintWidth_buf : number | string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (constraintWidth_buf_runtimeType))
        {
            const constraintWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let constraintWidth_buf_ : number | string | Resource | undefined
            if (constraintWidth_buf__selector == 0) {
                constraintWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (constraintWidth_buf__selector == 1) {
                constraintWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (constraintWidth_buf__selector == 2) {
                constraintWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for constraintWidth_buf_ has to be chosen through deserialisation.")
            }
            constraintWidth_buf = (constraintWidth_buf_ as number | string | Resource)
        }
        const constraintWidth_result : number | string | Resource | undefined = constraintWidth_buf
        const fontSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontSize_buf : number | string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (fontSize_buf_runtimeType))
        {
            const fontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let fontSize_buf_ : number | string | Resource | undefined
            if (fontSize_buf__selector == 0) {
                fontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontSize_buf__selector == 1) {
                fontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontSize_buf__selector == 2) {
                fontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontSize_buf_ has to be chosen through deserialisation.")
            }
            fontSize_buf = (fontSize_buf_ as number | string | Resource)
        }
        const fontSize_result : number | string | Resource | undefined = fontSize_buf
        const fontStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontStyle_buf : number | FontStyle | undefined
        if ((RuntimeType.UNDEFINED) != (fontStyle_buf_runtimeType))
        {
            const fontStyle_buf__selector : int32 = valueDeserializer.readInt8()
            let fontStyle_buf_ : number | FontStyle | undefined
            if (fontStyle_buf__selector == 0) {
                fontStyle_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontStyle_buf__selector == 1) {
                fontStyle_buf_ = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for fontStyle_buf_ has to be chosen through deserialisation.")
            }
            fontStyle_buf = (fontStyle_buf_ as number | FontStyle)
        }
        const fontStyle_result : number | FontStyle | undefined = fontStyle_buf
        const fontWeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontWeight_buf : number | string | FontWeight | undefined
        if ((RuntimeType.UNDEFINED) != (fontWeight_buf_runtimeType))
        {
            const fontWeight_buf__selector : int32 = valueDeserializer.readInt8()
            let fontWeight_buf_ : number | string | FontWeight | undefined
            if (fontWeight_buf__selector == 0) {
                fontWeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontWeight_buf__selector == 1) {
                fontWeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontWeight_buf__selector == 2) {
                fontWeight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for fontWeight_buf_ has to be chosen through deserialisation.")
            }
            fontWeight_buf = (fontWeight_buf_ as number | string | FontWeight)
        }
        const fontWeight_result : number | string | FontWeight | undefined = fontWeight_buf
        const fontFamily_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontFamily_buf : string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (fontFamily_buf_runtimeType))
        {
            const fontFamily_buf__selector : int32 = valueDeserializer.readInt8()
            let fontFamily_buf_ : string | Resource | undefined
            if (fontFamily_buf__selector == 0) {
                fontFamily_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontFamily_buf__selector == 1) {
                fontFamily_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontFamily_buf_ has to be chosen through deserialisation.")
            }
            fontFamily_buf = (fontFamily_buf_ as string | Resource)
        }
        const fontFamily_result : string | Resource | undefined = fontFamily_buf
        const letterSpacing_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let letterSpacing_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (letterSpacing_buf_runtimeType))
        {
            const letterSpacing_buf__selector : int32 = valueDeserializer.readInt8()
            let letterSpacing_buf_ : number | string | undefined
            if (letterSpacing_buf__selector == 0) {
                letterSpacing_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (letterSpacing_buf__selector == 1) {
                letterSpacing_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for letterSpacing_buf_ has to be chosen through deserialisation.")
            }
            letterSpacing_buf = (letterSpacing_buf_ as number | string)
        }
        const letterSpacing_result : number | string | undefined = letterSpacing_buf
        const textAlign_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textAlign_buf : text.TextAlign | undefined
        if ((RuntimeType.UNDEFINED) != (textAlign_buf_runtimeType))
        {
            textAlign_buf = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const textAlign_result : text.TextAlign | undefined = textAlign_buf
        const overflow_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let overflow_buf : number | TextOverflow | undefined
        if ((RuntimeType.UNDEFINED) != (overflow_buf_runtimeType))
        {
            const overflow_buf__selector : int32 = valueDeserializer.readInt8()
            let overflow_buf_ : number | TextOverflow | undefined
            if (overflow_buf__selector == 0) {
                overflow_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (overflow_buf__selector == 1) {
                overflow_buf_ = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for overflow_buf_ has to be chosen through deserialisation.")
            }
            overflow_buf = (overflow_buf_ as number | TextOverflow)
        }
        const overflow_result : number | TextOverflow | undefined = overflow_buf
        const maxLines_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let maxLines_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (maxLines_buf_runtimeType))
        {
            maxLines_buf = (valueDeserializer.readNumber() as number)
        }
        const maxLines_result : number | undefined = maxLines_buf
        const lineHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lineHeight_buf : number | string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (lineHeight_buf_runtimeType))
        {
            const lineHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let lineHeight_buf_ : number | string | Resource | undefined
            if (lineHeight_buf__selector == 0) {
                lineHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (lineHeight_buf__selector == 1) {
                lineHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (lineHeight_buf__selector == 2) {
                lineHeight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for lineHeight_buf_ has to be chosen through deserialisation.")
            }
            lineHeight_buf = (lineHeight_buf_ as number | string | Resource)
        }
        const lineHeight_result : number | string | Resource | undefined = lineHeight_buf
        const baselineOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let baselineOffset_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (baselineOffset_buf_runtimeType))
        {
            const baselineOffset_buf__selector : int32 = valueDeserializer.readInt8()
            let baselineOffset_buf_ : number | string | undefined
            if (baselineOffset_buf__selector == 0) {
                baselineOffset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (baselineOffset_buf__selector == 1) {
                baselineOffset_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for baselineOffset_buf_ has to be chosen through deserialisation.")
            }
            baselineOffset_buf = (baselineOffset_buf_ as number | string)
        }
        const baselineOffset_result : number | string | undefined = baselineOffset_buf
        const textCase_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textCase_buf : number | TextCase | undefined
        if ((RuntimeType.UNDEFINED) != (textCase_buf_runtimeType))
        {
            const textCase_buf__selector : int32 = valueDeserializer.readInt8()
            let textCase_buf_ : number | TextCase | undefined
            if (textCase_buf__selector == 0) {
                textCase_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (textCase_buf__selector == 1) {
                textCase_buf_ = TypeChecker.TextCase_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for textCase_buf_ has to be chosen through deserialisation.")
            }
            textCase_buf = (textCase_buf_ as number | TextCase)
        }
        const textCase_result : number | TextCase | undefined = textCase_buf
        const textIndent_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textIndent_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (textIndent_buf_runtimeType))
        {
            const textIndent_buf__selector : int32 = valueDeserializer.readInt8()
            let textIndent_buf_ : number | string | undefined
            if (textIndent_buf__selector == 0) {
                textIndent_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (textIndent_buf__selector == 1) {
                textIndent_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for textIndent_buf_ has to be chosen through deserialisation.")
            }
            textIndent_buf = (textIndent_buf_ as number | string)
        }
        const textIndent_result : number | string | undefined = textIndent_buf
        const wordBreak_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let wordBreak_buf : text.WordBreak | undefined
        if ((RuntimeType.UNDEFINED) != (wordBreak_buf_runtimeType))
        {
            wordBreak_buf = TypeChecker.text_WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreak_result : text.WordBreak | undefined = wordBreak_buf
        let value : MeasureOptions = ({textContent: textContent_result, constraintWidth: constraintWidth_result, fontSize: fontSize_result, fontStyle: fontStyle_result, fontWeight: fontWeight_result, fontFamily: fontFamily_result, letterSpacing: letterSpacing_result, textAlign: textAlign_result, overflow: overflow_result, maxLines: maxLines_result, lineHeight: lineHeight_result, baselineOffset: baselineOffset_result, textCase: textCase_result, textIndent: textIndent_result, wordBreak: wordBreak_result} as MeasureOptions)
        return value
    }
}

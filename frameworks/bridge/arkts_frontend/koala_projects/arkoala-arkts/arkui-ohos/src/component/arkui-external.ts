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

import { ResourceColor, Position, Length, SizeOptions, ResourceStr, Font } from "./units"
import { Color, TextOverflow, BorderStyle, TextHeightAdaptivePolicy } from "./enums"
import { FontOptions, FontInfo, UIFontConfig } from "@ohos/font"
import { MeasureOptions } from "@ohos/measure"
import { Resource } from "global.resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { PixelMap } from "#external"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Matrix4Transit } from "./arkui-matrix4"
import { EffectScope } from "./symbolglyph"

export class WebviewControllerInternal {
    public static fromPtr(ptr: KPointer): WebviewController {
        const obj : WebviewController = new WebviewController()
        obj.peer = new Finalizable(ptr, WebviewController.getFinalizer())
        return obj
    }
}
export class WebviewController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webviewcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebviewController_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = WebviewController.ctor_webviewcontroller()
        this.peer = new Finalizable(ctorPtr, WebviewController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebviewController_getFinalizer()
    }
    public static initializeWebEngine(): void {
        WebviewController.initializeWebEngine_serialize()
        return
    }
    public loadUrl(url: string | Resource, headers?: Array<WebHeader>): void {
        const url_casted = url as (string | Resource)
        const headers_casted = headers as (Array<WebHeader> | undefined)
        this.loadUrl_serialize(url_casted, headers_casted)
        return
    }
    private static initializeWebEngine_serialize(): void {
        ArkUIGeneratedNativeModule._WebviewController_initializeWebEngine()
    }
    private loadUrl_serialize(url: string | Resource, headers?: Array<WebHeader>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let url_type : int32 = RuntimeType.UNDEFINED
        url_type = runtimeType(url)
        if (RuntimeType.STRING == url_type) {
            thisSerializer.writeInt8(0 as int32)
            const url_0  = url as string
            thisSerializer.writeString(url_0)
        }
        else if (RuntimeType.OBJECT == url_type) {
            thisSerializer.writeInt8(1 as int32)
            const url_1  = url as Resource
            thisSerializer.writeResource(url_1)
        }
        let headers_type : int32 = RuntimeType.UNDEFINED
        headers_type = runtimeType(headers)
        thisSerializer.writeInt8(headers_type as int32)
        if ((RuntimeType.UNDEFINED) != (headers_type)) {
            const headers_value  = headers!
            thisSerializer.writeInt32(headers_value.length as int32)
            for (let i = 0; i < headers_value.length; i++) {
                const headers_value_element : WebHeader = headers_value[i]
                thisSerializer.writeWebHeader(headers_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebviewController_loadUrl(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class GlobalScope_ohos_arkui_componentSnapshot {
    public static get(id: string, callback: ((result: PixelMap) => void), options?: SnapshotOptions): void {
        const id_casted = id as (string)
        const callback_casted = callback as (((result: PixelMap) => void))
        const options_casted = options as (SnapshotOptions | undefined)
        GlobalScope_ohos_arkui_componentSnapshot.get_serialize(id_casted, callback_casted, options_casted)
        return
    }
    private static get_serialize(id: string, callback: ((result: PixelMap) => void), options?: SnapshotOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSnapshotOptions(options_value)
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
        const thisSerializer : Serializer = Serializer.hold()
        let note_type : int32 = RuntimeType.UNDEFINED
        note_type = runtimeType(note)
        thisSerializer.writeInt8(note_type as int32)
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
export class CommonShapeInternal {
    public static fromPtr(ptr: KPointer): CommonShape {
        const obj : CommonShape = new CommonShape()
        obj.peer = new Finalizable(ptr, CommonShape.getFinalizer())
        return obj
    }
}
export class CommonShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_commonshape(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CommonShape_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CommonShape.ctor_commonshape()
        this.peer = new Finalizable(ctorPtr, CommonShape.getFinalizer())
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(offset)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CommonShape {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8(0 as int32)
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1 as int32)
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2 as int32)
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3 as int32)
            const color_3  = color as Resource
            thisSerializer.writeResource(color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._CommonShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CommonShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(position)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
}
export class BaseShapeInternal {
    public static fromPtr(ptr: KPointer): BaseShape {
        const obj : BaseShape = new BaseShape()
        obj.peer = new Finalizable(ptr, BaseShape.getFinalizer())
        return obj
    }
}
export class BaseShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_baseshape(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = BaseShape.ctor_baseshape()
        this.peer = new Finalizable(ctorPtr, BaseShape.getFinalizer())
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
        const retval  = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, width)
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): BaseShape {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_height(this.peer!.ptr, height)
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): BaseShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(size)
        const retval  = ArkUIGeneratedNativeModule._BaseShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
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
    public static getInternalUIFontConfig(): UIFontConfig {
        return GlobalScope_ohos_font.getUIFontConfig_serialize()
    }
    private static registerFont_serialize(options: FontOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFontOptions(options)
        ArkUIGeneratedNativeModule._GlobalScope_ohos_font_registerFont(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getSystemFontList_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getSystemFontList()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : FontInfo = retvalDeserializer.readFontInfo()
        return returnResult
    }
    private static getUIFontConfig_serialize(): UIFontConfig {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getUIFontConfig() as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : UIFontConfig = retvalDeserializer.readUIFontConfig()
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMeasureOptions(options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureText(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static measureTextSize_serialize(options: MeasureOptions): SizeOptions {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMeasureOptions(options)
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureTextSize(thisSerializer.asBuffer(), thisSerializer.length()) as FixedArray<byte>
        thisSerializer.release()
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : SizeOptions = retvalDeserializer.readSizeOptions()
        return returnResult
    }
}
export interface TextModifier {
}
export enum RectWidthStyle {
    TIGHT = 0,
    MAX = 1
}
export enum RectHeightStyle {
    TIGHT = 0,
    MAX = 1,
    INCLUDE_LINE_SPACE_MIDDLE = 2,
    INCLUDE_LINE_SPACE_TOP = 3,
    INCLUDE_LINE_SPACE_BOTTOM = 4,
    STRUT = 5
}
export interface WebHeader {
    headerKey: string;
    headerValue: string;
}
export interface SnapshotRegion {
    left: number;
    right: number;
    top: number;
    bottom: number;
}
export interface LocalizedSnapshotRegion {
    start: number;
    end: number;
    top: number;
    bottom: number;
}
export type SnapshotRegionType = SnapshotRegion | LocalizedSnapshotRegion;
export interface SnapshotOptions {
    scale?: number;
    waitUntilRenderFinished?: boolean;
    region?: SnapshotRegionType;
}
export type AsyncCallback_image_PixelMap_Void = (result: PixelMap) => void;
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
export interface ShapeSize {
    width?: number | string;
    height?: number | string;
}
export interface RectShapeOptions extends ShapeSize {
    radius?: number | string | Array<number | string>;
}
export interface RoundRectShapeOptions extends ShapeSize {
    radiusWidth?: number | string;
    radiusHeight?: number | string;
}
export interface PathShapeOptions {
    commands?: string;
}
export interface Summary {
    summary: Map<string, int64>;
    totalSize: int64;
}
export type ReceiveCallback = (data: Map<string, Object>) => void;
export enum ResolutionQuality {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
}
export type ImageMatrix = Matrix4Transit;
export enum IntentionCode {
    INTENTION_UNKNOWN = -1,
    INTENTION_UP = 1,
    INTENTION_DOWN = 2,
    INTENTION_LEFT = 3,
    INTENTION_RIGHT = 4,
    INTENTION_SELECT = 5,
    INTENTION_ESCAPE = 6,
    INTENTION_BACK = 7,
    INTENTION_FORWARD = 8,
    INTENTION_MENU = 9,
    INTENTION_PAGE_UP = 11,
    INTENTION_PAGE_DOWN = 12,
    INTENTION_ZOOM_OUT = 13,
    INTENTION_ZOOM_IN = 14
}
export enum WindowStatusType {
    UNDEFINED = 0,
    FULL_SCREEN = 1,
    MAXIMIZE = 2,
    MINIMIZE = 3,
    FLOATING = 4,
    SPLIT_SCREEN = 5
}
export interface ImageModifier {
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
export interface LabelStyle {
    overflow?: TextOverflow;
    maxLines?: number;
    minFontSize?: number | ResourceStr;
    maxFontSize?: number | ResourceStr;
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}

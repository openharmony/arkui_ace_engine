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

import { RichEditorBaseController, RichEditorBaseControllerInternal } from "./ArkRichEditorBaseControllerMaterialized"
import { TextEditControllerEx, TextEditControllerExInternal } from "./ArkTextEditControllerExMaterialized"
import { TextBaseController, TextBaseControllerInternal } from "./ArkTextBaseControllerMaterialized"
import { SelectionOptions, CustomBuilder, ShadowOptions, ShadowType, MenuPolicy, EventTarget, SourceType, SourceTool, DrawContext } from "./ArkCommonInterfaces"
import { LayoutManager, LayoutManagerInternal } from "./ArkLayoutManagerMaterialized"
import { PreviewText, DecorationStyleResult, PositionWithAffinity, LineMetrics, TextRange, TextBox, Affinity } from "./ArkTextCommonInterfaces"
import { RichEditorTextStyle, RichEditorTextSpanOptions, RichEditorImageSpanOptions, RichEditorBuilderSpanOptions, RichEditorSymbolSpanOptions, RichEditorUpdateTextSpanStyleOptions, RichEditorUpdateImageSpanStyleOptions, RichEditorUpdateSymbolSpanStyleOptions, RichEditorParagraphStyleOptions, RichEditorRange, RichEditorImageSpanResult, RichEditorTextSpanResult, RichEditorParagraphResult, RichEditorSelection, RichEditorSpan, RichEditorSpanPosition, RichEditorImageSpanStyleResult, RichEditorLayoutStyle, RichEditorTextStyleResult, RichEditorSymbolSpanStyle, RichEditorParagraphStyle, LeadingMarginPlaceholder, RichEditorGesture, RichEditorImageSpanStyle, RichEditorSpanStyleOptions } from "./ArkRichEditorInterfaces"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { ResourceStr, Dimension, Margin, BorderRadiuses, Length, ResourceColor, PX, VP, FP, LPX, Percentage, Padding, Area, Position, SizeOptions } from "./ArkUnitsInterfaces"
import { CustomNodeBuilder } from "./ArkCustomBuilderInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { StyledString, StyledStringInternal } from "./ArkStyledStringMaterialized"
import { ImageSpanAlignment, ImageFit, FontStyle, TextDecorationType, TextDecorationStyle, Color, ColoringStrategy, FontWeight, TextAlign, WordBreak, LineBreakStrategy } from "./ArkEnumsInterfaces"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./ArkSymbolglyphInterfaces"
import { RectWidthStyle, RectHeightStyle, LengthUnit } from "./ArkArkuiExternalInterfaces"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { ClickEvent, ClickEventInternal } from "./ArkClickEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { GestureEvent, GestureEventInternal } from "./ArkGestureEventMaterialized"
import { FingerInfo } from "./ArkGestureInterfaces"
import { ImageAttachment, ImageAttachmentInternal } from "./ArkImageAttachmentMaterialized"
import { CustomSpan, CustomSpanInternal } from "./ArkCustomSpanMaterialized"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class RichEditorControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorController {
        const obj: RichEditorController = new RichEditorController()
        obj.peer = new Finalizable(ptr, RichEditorController.getFinalizer())
        return obj
    }
}
export class RichEditorController extends RichEditorBaseController implements MaterializedBase {
    static ctor_richeditorcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._RichEditorController_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = RichEditorController.ctor_richeditorcontroller()
        this.peer = new Finalizable(ctorPtr, RichEditorController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorController_getFinalizer()
    }
    public addTextSpan(value: string, options?: RichEditorTextSpanOptions): number {
        const value_casted = value as (string)
        const options_casted = options as (RichEditorTextSpanOptions | undefined)
        return this.addTextSpan_serialize(value_casted, options_casted)
    }
    public addImageSpan(value: PixelMap | ResourceStr, options?: RichEditorImageSpanOptions): number {
        const value_casted = value as (PixelMap | ResourceStr)
        const options_casted = options as (RichEditorImageSpanOptions | undefined)
        return this.addImageSpan_serialize(value_casted, options_casted)
    }
    public addBuilderSpan(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): number {
        const value_casted = value as (CustomBuilder)
        const options_casted = options as (RichEditorBuilderSpanOptions | undefined)
        return this.addBuilderSpan_serialize(value_casted, options_casted)
    }
    public addSymbolSpan(value: Resource, options?: RichEditorSymbolSpanOptions): number {
        const value_casted = value as (Resource)
        const options_casted = options as (RichEditorSymbolSpanOptions | undefined)
        return this.addSymbolSpan_serialize(value_casted, options_casted)
    }
    public updateSpanStyle(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const value_casted = value as (RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions)
        this?.updateSpanStyle_serialize(value_casted)
        return
    }
    public updateParagraphStyle(value: RichEditorParagraphStyleOptions): void {
        const value_casted = value as (RichEditorParagraphStyleOptions)
        this?.updateParagraphStyle_serialize(value_casted)
        return
    }
    public deleteSpans(value?: RichEditorRange): void {
        const value_casted = value as (RichEditorRange | undefined)
        this?.deleteSpans_serialize(value_casted)
        return
    }
    public getSpans(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> {
        const value_casted = value as (RichEditorRange | undefined)
        return this.getSpans_serialize(value_casted)
    }
    public getParagraphs(value?: RichEditorRange): Array<RichEditorParagraphResult> {
        const value_casted = value as (RichEditorRange | undefined)
        return this.getParagraphs_serialize(value_casted)
    }
    public getSelection(): RichEditorSelection {
        return this.getSelection_serialize()
    }
    public fromStyledString(value: StyledString): Array<RichEditorSpan> {
        const value_casted = value as (StyledString)
        return this.fromStyledString_serialize(value_casted)
    }
    public toStyledString(value: RichEditorRange): StyledString {
        const value_casted = value as (RichEditorRange)
        return this.toStyledString_serialize(value_casted)
    }
    private addTextSpan_serialize(value: string, options?: RichEditorTextSpanOptions): number {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeRichEditorTextSpanOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._RichEditorController_addTextSpan(this.peer!.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addImageSpan_serialize(value: PixelMap | ResourceStr, options?: RichEditorImageSpanOptions): number {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<PixelMap>(value)
            thisSerializer.writePixelMap(value_0)
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<ResourceStr>(value)
            let value_1_type: int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0)
                const value_1_0 = unsafeCast<string>(value_1)
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(1)
                const value_1_1 = unsafeCast<Resource>(value_1)
                thisSerializer.writeResource(value_1_1)
            }
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeRichEditorImageSpanOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._RichEditorController_addImageSpan(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addBuilderSpan_serialize(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): number {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeRichEditorBuilderSpanOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._RichEditorController_addBuilderSpan(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addSymbolSpan_serialize(value: Resource, options?: RichEditorSymbolSpanOptions): number {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeRichEditorSymbolSpanOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._RichEditorController_addSymbolSpan(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateSpanStyle_serialize(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("textStyle")))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<RichEditorUpdateTextSpanStyleOptions>(value)
            thisSerializer.writeRichEditorUpdateTextSpanStyleOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("imageStyle")))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<RichEditorUpdateImageSpanStyleOptions>(value)
            thisSerializer.writeRichEditorUpdateImageSpanStyleOptions(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("symbolStyle")))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<RichEditorUpdateSymbolSpanStyleOptions>(value)
            thisSerializer.writeRichEditorUpdateSymbolSpanStyleOptions(value_2)
        }
        ArkUIGeneratedNativeModule._RichEditorController_updateSpanStyle(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private updateParagraphStyle_serialize(value: RichEditorParagraphStyleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeRichEditorParagraphStyleOptions(value)
        ArkUIGeneratedNativeModule._RichEditorController_updateParagraphStyle(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private deleteSpans_serialize(value?: RichEditorRange): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeRichEditorRange(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorController_deleteSpans(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSpans_serialize(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeRichEditorRange(value_value)
        }
        const retval = ArkUIGeneratedNativeModule._RichEditorController_getSpans(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<RichEditorImageSpanResult | RichEditorTextSpanResult> = new Array<RichEditorImageSpanResult | RichEditorTextSpanResult>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_selector: number = retvalDeserializer.readInt8()
            let buffer_buf: RichEditorImageSpanResult | RichEditorTextSpanResult | undefined|undefined 
            if (buffer_buf_selector == 0) {
                buffer_buf = retvalDeserializer.readRichEditorImageSpanResult()
            }
            else if (buffer_buf_selector == 1) {
                buffer_buf = retvalDeserializer.readRichEditorTextSpanResult()
            }
            else {
                throw new Error("One of the branches for buffer_buf has to be chosen through deserialisation.")
            }
            buffer[buffer_i] = (buffer_buf as RichEditorImageSpanResult | RichEditorTextSpanResult)
        }
        const returnResult: Array<RichEditorImageSpanResult | RichEditorTextSpanResult> = buffer
        return returnResult
    }
    private getParagraphs_serialize(value?: RichEditorRange): Array<RichEditorParagraphResult> {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeRichEditorRange(value_value)
        }
        const retval = ArkUIGeneratedNativeModule._RichEditorController_getParagraphs(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<RichEditorParagraphResult> = new Array<RichEditorParagraphResult>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readRichEditorParagraphResult()
        }
        const returnResult: Array<RichEditorParagraphResult> = buffer
        return returnResult
    }
    private getSelection_serialize(): RichEditorSelection {
        const retval = ArkUIGeneratedNativeModule._RichEditorController_getSelection(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: RichEditorSelection = retvalDeserializer.readRichEditorSelection()
        return returnResult
    }
    private fromStyledString_serialize(value: StyledString): Array<RichEditorSpan> {
        const retval = ArkUIGeneratedNativeModule._RichEditorController_fromStyledString(this.peer!.ptr, toPeerPtr(value))
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<RichEditorSpan> = new Array<RichEditorSpan>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_selector: number = retvalDeserializer.readInt8()
            let buffer_buf: RichEditorImageSpanResult | RichEditorTextSpanResult | undefined|undefined 
            if (buffer_buf_selector == 0) {
                buffer_buf = retvalDeserializer.readRichEditorImageSpanResult()
            }
            else if (buffer_buf_selector == 1) {
                buffer_buf = retvalDeserializer.readRichEditorTextSpanResult()
            }
            else {
                throw new Error("One of the branches for buffer_buf has to be chosen through deserialisation.")
            }
            buffer[buffer_i] = (buffer_buf as RichEditorImageSpanResult | RichEditorTextSpanResult)
        }
        const returnResult: Array<RichEditorSpan> = buffer
        return returnResult
    }
    private toStyledString_serialize(value: RichEditorRange): StyledString {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeRichEditorRange(value)
        const retval = ArkUIGeneratedNativeModule._RichEditorController_toStyledString(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: StyledString = StyledStringInternal.fromPtr(retval)
        return obj
    }
}

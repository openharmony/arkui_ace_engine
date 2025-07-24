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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ResourceColor, SizeOptions, ColorFilter, ColorFilterInternal, ResourceStr, Padding, BorderRadiuses } from "./units"
import { FontStyle, Color, TextDecorationType, TextDecorationStyle, TextAlign, TextOverflow, WordBreak, ImageSpanAlignment, ImageFit, FontWeight } from "./enums"
import { Resource } from "global/resource"
import { DrawContext } from "./../Graphics"
import { LengthMetrics } from "../Graphics"
import { ShadowOptions, Callback_ClickEvent_Void, ClickEvent } from "./common"
import { TextBackgroundStyle } from "./span"
import { LeadingMarginPlaceholder } from "./richEditor"
import { PixelMap, PixelMapInternal } from "./arkui-pixelmap"
import { DrawingColorFilter, DrawingColorFilterInternal } from "./arkui-drawing"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Callback_GestureEvent_Void, GestureEvent } from "./gesture"
export class StyledStringInternal {
    public static fromPtr(ptr: KPointer): StyledString {
        const obj : StyledString = new StyledString(undefined, undefined)
        obj.peer = new Finalizable(ptr, StyledString.getFinalizer())
        return obj
    }
}
export class StyledString implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get length(): number {
        return this.getLength()
    }
    static ctor_styledstring(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isImageAttachment(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as ImageAttachment
            thisSerializer.writeImageAttachment(value_1)
        }
        else if (TypeChecker.isCustomSpan(value)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as CustomSpan
            thisSerializer.writeCustomSpan(value_2)
        }
        let styles_type : int32 = RuntimeType.UNDEFINED
        styles_type = runtimeType(styles)
        thisSerializer.writeInt8(styles_type as int32)
        if ((RuntimeType.UNDEFINED) != (styles_type)) {
            const styles_value  = styles!
            thisSerializer.writeInt32(styles_value.length as int32)
            for (let i = 0; i < styles_value.length; i++) {
                const styles_value_element : StyleOptions = styles_value[i]
                thisSerializer.writeStyleOptions(styles_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>) {
        if (((value) !== (undefined)) || ((styles) !== (undefined)))
        {
            const ctorPtr : KPointer = StyledString.ctor_styledstring((value)!, styles)
            this.peer = new Finalizable(ctorPtr, StyledString.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledString_getFinalizer()
    }
    public getString(): string {
        return this.getString_serialize()
    }
    public getStyles(start: number, length: number, styledKey?: StyledStringKey): Array<SpanStyle> {
        const start_casted = start as (number)
        const length_casted = length as (number)
        const styledKey_casted = styledKey as (StyledStringKey | undefined)
        return this.getStyles_serialize(start_casted, length_casted, styledKey_casted)
    }
    public equals(other: StyledString): boolean {
        const other_casted = other as (StyledString)
        return this.equals_serialize(other_casted)
    }
    public subStyledString(start: number, length?: number): StyledString {
        const start_casted = start as (number)
        const length_casted = length as (number | undefined)
        return this.subStyledString_serialize(start_casted, length_casted)
    }
    public static fromHtml(html: string): Promise<StyledString> {
        const html_casted = html as (string)
        return StyledString.fromHtml_serialize(html_casted)
    }
    public static toHtml(styledString: StyledString): string {
        const styledString_casted = styledString as (StyledString)
        return StyledString.toHtml_serialize(styledString_casted)
    }
    public static marshalling(styledString: StyledString, callback_?: StyledStringMarshallCallback): NativeBuffer {
        const styledString_type = runtimeType(styledString)
        const callback__type = runtimeType(callback_)
        const styledString_casted = styledString as (StyledString)
        return StyledString.marshalling1_serialize(styledString_casted)
    }
    public static unmarshalling(buffer: NativeBuffer, callback_?: StyledStringUnmarshallCallback): Promise<StyledString> {
        const buffer_type = runtimeType(buffer)
        const callback__type = runtimeType(callback_)
        const buffer_casted = buffer as (NativeBuffer)
        return StyledString.unmarshalling1_serialize(buffer_casted)
    }
    private getLength(): number {
        return this.getLength_serialize()
    }
    private getString_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._StyledString_getString(this.peer!.ptr)
        return retval
    }
    private getStyles_serialize(start: number, length: number, styledKey?: StyledStringKey): Array<SpanStyle> {
        const thisSerializer : Serializer = Serializer.hold()
        let styledKey_type : int32 = RuntimeType.UNDEFINED
        styledKey_type = runtimeType(styledKey)
        thisSerializer.writeInt8(styledKey_type as int32)
        if ((RuntimeType.UNDEFINED) != (styledKey_type)) {
            const styledKey_value  = (styledKey as StyledStringKey)
            thisSerializer.writeInt32(TypeChecker.StyledStringKey_ToNumeric(styledKey_value))
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_getStyles(this.peer!.ptr, start, length, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<SpanStyle> = new Array<SpanStyle>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readSpanStyle()
        }
        const returnResult : Array<SpanStyle> = buffer
        return returnResult
    }
    private equals_serialize(other: StyledString): boolean {
        const retval  = ArkUIGeneratedNativeModule._StyledString_equals(this.peer!.ptr, toPeerPtr(other))
        return retval
    }
    private subStyledString_serialize(start: number, length?: number): StyledString {
        const thisSerializer : Serializer = Serializer.hold()
        let length_type : int32 = RuntimeType.UNDEFINED
        length_type = runtimeType(length)
        thisSerializer.writeInt8(length_type as int32)
        if ((RuntimeType.UNDEFINED) != (length_type)) {
            const length_value  = length!
            thisSerializer.writeNumber(length_value)
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_subStyledString(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : StyledString = StyledStringInternal.fromPtr(retval)
        return obj
    }
    private static fromHtml_serialize(html: string): Promise<StyledString> {
        const thisSerializer : Serializer = Serializer.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString>()[0]
        ArkUIGeneratedNativeModule._StyledString_fromHtml(html, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static toHtml_serialize(styledString: StyledString): string {
        const retval  = ArkUIGeneratedNativeModule._StyledString_toHtml(toPeerPtr(styledString))
        return retval
    }
    private static marshalling0_serialize(styledString: StyledString, callback_: StyledStringMarshallCallback): NativeBuffer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        const retval  = ArkUIGeneratedNativeModule._StyledString_marshalling0(toPeerPtr(styledString), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return new Deserializer(retval, retval.length as int32).readBuffer()
    }
    private static marshalling1_serialize(styledString: StyledString): NativeBuffer {
        const retval  = ArkUIGeneratedNativeModule._StyledString_marshalling1(toPeerPtr(styledString))
        return new Deserializer(retval, retval.length as int32).readBuffer()
    }
    private static unmarshalling0_serialize(buffer: NativeBuffer, callback_: StyledStringUnmarshallCallback): Promise<StyledString> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBuffer(buffer)
        thisSerializer.holdAndWriteCallback(callback_)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString>()[0]
        ArkUIGeneratedNativeModule._StyledString_unmarshalling0(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static unmarshalling1_serialize(buffer: NativeBuffer): Promise<StyledString> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBuffer(buffer)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString>()[0]
        ArkUIGeneratedNativeModule._StyledString_unmarshalling1(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getLength_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._StyledString_getLength(this.peer!.ptr)
        return retval
    }
}
export class TextStyle_styled_stringInternal {
    public static fromPtr(ptr: KPointer): TextStyle {
        const obj : TextStyle = new TextStyle(undefined)
        obj.peer = new Finalizable(ptr, TextStyle.getFinalizer())
        return obj
    }
}
export class TextStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get fontColor(): ResourceColor | undefined {
        throw new Error("Not implemented")
    }
    get fontFamily(): string | undefined {
        return this.getFontFamily()
    }
    get fontSize(): number | undefined {
        return this.getFontSize()
    }
    get fontWeight(): number | undefined {
        return this.getFontWeight()
    }
    get fontStyle(): FontStyle | undefined {
        return this.getFontStyle()
    }
    static ctor_textstyle_styled_string(value?: TextStyleInterface): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextStyleInterface(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextStyle_styled_string_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: TextStyleInterface) {
        const ctorPtr : KPointer = TextStyle.ctor_textstyle_styled_string(value)
        this.peer = new Finalizable(ctorPtr, TextStyle.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextStyle_styled_string_getFinalizer()
    }
    private getFontColor(): ResourceColor | undefined {
        return this.getFontColor_serialize()
    }
    private getFontFamily(): string | undefined {
        return this.getFontFamily_serialize()
    }
    private getFontSize(): number | undefined {
        return this.getFontSize_serialize()
    }
    private getFontWeight(): number | undefined {
        return this.getFontWeight_serialize()
    }
    private getFontStyle(): FontStyle | undefined {
        return this.getFontStyle_serialize()
    }
    private getFontColor_serialize(): ResourceColor | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontColor(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getFontFamily_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontFamily(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getFontSize_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontSize(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getFontWeight_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontWeight(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getFontStyle_serialize(): FontStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
export class DecorationStyleInternal {
    public static fromPtr(ptr: KPointer): DecorationStyle {
        const obj : DecorationStyle = new DecorationStyle(undefined)
        obj.peer = new Finalizable(ptr, DecorationStyle.getFinalizer())
        return obj
    }
}
export class DecorationStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get type(): TextDecorationType {
        return this.getType()
    }
    get color(): ResourceColor | undefined {
        throw new Error("Not implemented")
    }
    get style(): TextDecorationStyle | undefined {
        return this.getStyle()
    }
    static ctor_decorationstyle(value: DecorationStyleInterface): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDecorationStyleInterface(value)
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: DecorationStyleInterface) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = DecorationStyle.ctor_decorationstyle((value)!)
            this.peer = new Finalizable(ctorPtr, DecorationStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DecorationStyle_getFinalizer()
    }
    private getType(): TextDecorationType {
        return this.getType_serialize()
    }
    private getColor(): ResourceColor | undefined {
        return this.getColor_serialize()
    }
    private getStyle(): TextDecorationStyle | undefined {
        return this.getStyle_serialize()
    }
    private getType_serialize(): TextDecorationType {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getType(this.peer!.ptr)
        return TypeChecker.TextDecorationType_FromNumeric(retval)
    }
    private getColor_serialize(): ResourceColor | undefined {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getColor(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getStyle_serialize(): TextDecorationStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
export class BaselineOffsetStyleInternal {
    public static fromPtr(ptr: KPointer): BaselineOffsetStyle {
        const obj : BaselineOffsetStyle = new BaselineOffsetStyle(undefined)
        obj.peer = new Finalizable(ptr, BaselineOffsetStyle.getFinalizer())
        return obj
    }
}
export class BaselineOffsetStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get baselineOffset(): number {
        return this.getBaselineOffset()
    }
    static ctor_baselineoffsetstyle(value: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_ctor(toPeerPtr(value))
        return retval
    }
    constructor(value?: LengthMetrics) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = BaselineOffsetStyle.ctor_baselineoffsetstyle((value)!)
            this.peer = new Finalizable(ctorPtr, BaselineOffsetStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaselineOffsetStyle_getFinalizer()
    }
    private getBaselineOffset(): number {
        return this.getBaselineOffset_serialize()
    }
    private getBaselineOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_getBaselineOffset(this.peer!.ptr)
        return retval
    }
}
export class LetterSpacingStyleInternal {
    public static fromPtr(ptr: KPointer): LetterSpacingStyle {
        const obj : LetterSpacingStyle = new LetterSpacingStyle(undefined)
        obj.peer = new Finalizable(ptr, LetterSpacingStyle.getFinalizer())
        return obj
    }
}
export class LetterSpacingStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get letterSpacing(): number {
        return this.getLetterSpacing()
    }
    static ctor_letterspacingstyle(value: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_ctor(toPeerPtr(value))
        return retval
    }
    constructor(value?: LengthMetrics) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = LetterSpacingStyle.ctor_letterspacingstyle((value)!)
            this.peer = new Finalizable(ctorPtr, LetterSpacingStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LetterSpacingStyle_getFinalizer()
    }
    private getLetterSpacing(): number {
        return this.getLetterSpacing_serialize()
    }
    private getLetterSpacing_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_getLetterSpacing(this.peer!.ptr)
        return retval
    }
}
export class TextShadowStyleInternal {
    public static fromPtr(ptr: KPointer): TextShadowStyle {
        const obj : TextShadowStyle = new TextShadowStyle(undefined)
        obj.peer = new Finalizable(ptr, TextShadowStyle.getFinalizer())
        return obj
    }
}
export class TextShadowStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get textShadow(): Array<ShadowOptions> {
        throw new Error("Not implemented")
    }
    static ctor_textshadowstyle(value: ShadowOptions | Array<ShadowOptions>): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isShadowOptions(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ShadowOptions
            thisSerializer.writeShadowOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_ShadowOptions(value))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Array<ShadowOptions>
            thisSerializer.writeInt32(value_1.length as int32)
            for (let i = 0; i < value_1.length; i++) {
                const value_1_element : ShadowOptions = value_1[i]
                thisSerializer.writeShadowOptions(value_1_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextShadowStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: ShadowOptions | Array<ShadowOptions>) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = TextShadowStyle.ctor_textshadowstyle((value)!)
            this.peer = new Finalizable(ctorPtr, TextShadowStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextShadowStyle_getFinalizer()
    }
    private getTextShadow(): Array<ShadowOptions> {
        return this.getTextShadow_serialize()
    }
    private getTextShadow_serialize(): Array<ShadowOptions> {
        const retval  = ArkUIGeneratedNativeModule._TextShadowStyle_getTextShadow(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<ShadowOptions> = new Array<ShadowOptions>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readShadowOptions()
        }
        const returnResult : Array<ShadowOptions> = buffer
        return returnResult
    }
}
export class BackgroundColorStyleInternal {
    public static fromPtr(ptr: KPointer): BackgroundColorStyle {
        const obj : BackgroundColorStyle = new BackgroundColorStyle(undefined)
        obj.peer = new Finalizable(ptr, BackgroundColorStyle.getFinalizer())
        return obj
    }
}
export class BackgroundColorStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get textBackgroundStyle(): TextBackgroundStyle {
        throw new Error("Not implemented")
    }
    static ctor_backgroundcolorstyle(textBackgroundStyle: TextBackgroundStyle): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextBackgroundStyle(textBackgroundStyle)
        const retval  = ArkUIGeneratedNativeModule._BackgroundColorStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(textBackgroundStyle?: TextBackgroundStyle) {
        if ((textBackgroundStyle) !== (undefined))
        {
            const ctorPtr : KPointer = BackgroundColorStyle.ctor_backgroundcolorstyle((textBackgroundStyle)!)
            this.peer = new Finalizable(ctorPtr, BackgroundColorStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BackgroundColorStyle_getFinalizer()
    }
    private getTextBackgroundStyle(): TextBackgroundStyle {
        return this.getTextBackgroundStyle_serialize()
    }
    private getTextBackgroundStyle_serialize(): TextBackgroundStyle {
        const retval  = ArkUIGeneratedNativeModule._BackgroundColorStyle_getTextBackgroundStyle(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : TextBackgroundStyle = retvalDeserializer.readTextBackgroundStyle()
        return returnResult
    }
}
export class GestureStyleInternal {
    public static fromPtr(ptr: KPointer): GestureStyle {
        const obj : GestureStyle = new GestureStyle(undefined)
        obj.peer = new Finalizable(ptr, GestureStyle.getFinalizer())
        return obj
    }
}
export class GestureStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturestyle(value?: GestureStyleInterface): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeGestureStyleInterface(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._GestureStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: GestureStyleInterface) {
        const ctorPtr : KPointer = GestureStyle.ctor_gesturestyle(value)
        this.peer = new Finalizable(ctorPtr, GestureStyle.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureStyle_getFinalizer()
    }
}
export class ParagraphStyleInternal {
    public static fromPtr(ptr: KPointer): ParagraphStyle {
        const obj : ParagraphStyle = new ParagraphStyle(undefined)
        obj.peer = new Finalizable(ptr, ParagraphStyle.getFinalizer())
        return obj
    }
}
export class ParagraphStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get textAlign(): TextAlign | undefined {
        return this.getTextAlign()
    }
    get textIndent(): number | undefined {
        return this.getTextIndent()
    }
    get maxLines(): number | undefined {
        return this.getMaxLines()
    }
    get overflow(): TextOverflow | undefined {
        return this.getOverflow()
    }
    get wordBreak(): WordBreak | undefined {
        return this.getWordBreak()
    }
    get leadingMargin(): number | LeadingMarginPlaceholder | undefined {
        throw new Error("Not implemented")
    }
    get paragraphSpacing(): number | undefined {
        return this.getParagraphSpacing()
    }
    static ctor_paragraphstyle(value?: ParagraphStyleInterface): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeParagraphStyleInterface(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: ParagraphStyleInterface) {
        const ctorPtr : KPointer = ParagraphStyle.ctor_paragraphstyle(value)
        this.peer = new Finalizable(ctorPtr, ParagraphStyle.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ParagraphStyle_getFinalizer()
    }
    private getTextAlign(): TextAlign | undefined {
        return this.getTextAlign_serialize()
    }
    private getTextIndent(): number | undefined {
        return this.getTextIndent_serialize()
    }
    private getMaxLines(): number | undefined {
        return this.getMaxLines_serialize()
    }
    private getOverflow(): TextOverflow | undefined {
        return this.getOverflow_serialize()
    }
    private getWordBreak(): WordBreak | undefined {
        return this.getWordBreak_serialize()
    }
    private getLeadingMargin(): number | LeadingMarginPlaceholder | undefined {
        return this.getLeadingMargin_serialize()
    }
    private getParagraphSpacing(): number | undefined {
        return this.getParagraphSpacing_serialize()
    }
    private getTextAlign_serialize(): TextAlign | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getTextAlign(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getTextIndent_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getTextIndent(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getMaxLines_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getMaxLines(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getOverflow_serialize(): TextOverflow | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getOverflow(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getWordBreak_serialize(): WordBreak | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getWordBreak(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getLeadingMargin_serialize(): number | LeadingMarginPlaceholder | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getLeadingMargin(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getParagraphSpacing_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getParagraphSpacing(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
export class LineHeightStyleInternal {
    public static fromPtr(ptr: KPointer): LineHeightStyle {
        const obj : LineHeightStyle = new LineHeightStyle(undefined)
        obj.peer = new Finalizable(ptr, LineHeightStyle.getFinalizer())
        return obj
    }
}
export class LineHeightStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get lineHeight(): number {
        return this.getLineHeight()
    }
    static ctor_lineheightstyle(lineHeight: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_ctor(toPeerPtr(lineHeight))
        return retval
    }
    constructor(lineHeight?: LengthMetrics) {
        if ((lineHeight) !== (undefined))
        {
            const ctorPtr : KPointer = LineHeightStyle.ctor_lineheightstyle((lineHeight)!)
            this.peer = new Finalizable(ctorPtr, LineHeightStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LineHeightStyle_getFinalizer()
    }
    private getLineHeight(): number {
        return this.getLineHeight_serialize()
    }
    private getLineHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_getLineHeight(this.peer!.ptr)
        return retval
    }
}
export class UrlStyleInternal {
    public static fromPtr(ptr: KPointer): UrlStyle {
        const obj : UrlStyle = new UrlStyle(undefined)
        obj.peer = new Finalizable(ptr, UrlStyle.getFinalizer())
        return obj
    }
}
export class UrlStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get url(): string {
        return this.getUrl()
    }
    static ctor_urlstyle(url: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UrlStyle_ctor(url)
        return retval
    }
    constructor(url?: string) {
        if ((url) !== (undefined))
        {
            const ctorPtr : KPointer = UrlStyle.ctor_urlstyle((url)!)
            this.peer = new Finalizable(ctorPtr, UrlStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UrlStyle_getFinalizer()
    }
    private getUrl(): string {
        return this.getUrl_serialize()
    }
    private getUrl_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._UrlStyle_getUrl(this.peer!.ptr)
        return retval
    }
}
export class ImageAttachmentInternal {
    public static fromPtr(ptr: KPointer): ImageAttachment {
        const obj : ImageAttachment = new ImageAttachment(undefined)
        obj.peer = new Finalizable(ptr, ImageAttachment.getFinalizer())
        return obj
    }
}
export class ImageAttachment implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get value(): PixelMap {
        return this.getValue()
    }
    get size(): SizeOptions | undefined {
        throw new Error("Not implemented")
    }
    get verticalAlign(): ImageSpanAlignment | undefined {
        return this.getVerticalAlign()
    }
    get objectFit(): ImageFit | undefined {
        return this.getObjectFit()
    }
    get layoutStyle(): ImageAttachmentLayoutStyle | undefined {
        throw new Error("Not implemented")
    }
    get colorFilter(): ColorFilterType | undefined {
        throw new Error("Not implemented")
    }
    static ctor_imageattachment(value: ImageAttachmentInterface): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAttachmentInterface(value)
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: ImageAttachmentInterface) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = ImageAttachment.ctor_imageattachment((value)!)
            this.peer = new Finalizable(ctorPtr, ImageAttachment.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageAttachment_getFinalizer()
    }
    private getValue(): PixelMap {
        return this.getValue_serialize()
    }
    private getSize(): SizeOptions | undefined {
        return this.getSize_serialize()
    }
    private getVerticalAlign(): ImageSpanAlignment | undefined {
        return this.getVerticalAlign_serialize()
    }
    private getObjectFit(): ImageFit | undefined {
        return this.getObjectFit_serialize()
    }
    private getLayoutStyle(): ImageAttachmentLayoutStyle | undefined {
        return this.getLayoutStyle_serialize()
    }
    private getColorFilter(): ColorFilterType | undefined {
        return this.getColorFilter_serialize()
    }
    private getValue_serialize(): PixelMap {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getValue(this.peer!.ptr)
        const obj : PixelMap = PixelMapInternal.fromPtr(retval)
        return obj
    }
    private getSize_serialize(): SizeOptions | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getSize(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getVerticalAlign_serialize(): ImageSpanAlignment | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getVerticalAlign(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getObjectFit_serialize(): ImageFit | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getObjectFit(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getLayoutStyle_serialize(): ImageAttachmentLayoutStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getLayoutStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getColorFilter_serialize(): ColorFilterType | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getColorFilter(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
export class CustomSpanInternal {
    public static fromPtr(ptr: KPointer): CustomSpan {
        const obj : CustomSpan = new CustomSpan()
        obj.peer = new Finalizable(ptr, CustomSpan.getFinalizer())
        return obj
    }
}
export class CustomSpan implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_customspan(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CustomSpan.ctor_customspan()
        this.peer = new Finalizable(ctorPtr, CustomSpan.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomSpan_getFinalizer()
    }
    public onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
        const measureInfo_casted = measureInfo as (CustomSpanMeasureInfo)
        return this.onMeasure_serialize(measureInfo_casted)
    }
    public onDraw(context: DrawContext, drawInfo: CustomSpanDrawInfo): void {
        const context_casted = context as (DrawContext)
        const drawInfo_casted = drawInfo as (CustomSpanDrawInfo)
        this.onDraw_serialize(context_casted, drawInfo_casted)
        return
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private onMeasure_serialize(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomSpanMeasureInfo(measureInfo)
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_onMeasure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : CustomSpanMetrics = retvalDeserializer.readCustomSpanMetrics()
        return returnResult
    }
    private onDraw_serialize(context: DrawContext, drawInfo: CustomSpanDrawInfo): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(context)
        thisSerializer.writeCustomSpanDrawInfo(drawInfo)
        ArkUIGeneratedNativeModule._CustomSpan_onDraw(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._CustomSpan_invalidate(this.peer!.ptr)
    }
}
export type StyledStringMarshallingValue = UserDataSpan;
export type StyledStringMarshallCallback = (marshallableVal: UserDataSpan) => NativeBuffer;
export type StyledStringUnmarshallCallback = (buf: NativeBuffer) => UserDataSpan;
export interface StyleOptions {
    start?: number;
    length?: number;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
export interface SpanStyle {
    start: number;
    length: number;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
export interface TextStyleInterface {
    fontColor?: ResourceColor;
    fontFamily?: ResourceStr;
    fontSize?: LengthMetrics;
    fontWeight?: number | FontWeight | string;
    fontStyle?: FontStyle;
}
export interface DecorationStyleInterface {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
export interface GestureStyleInterface {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: ((event: GestureEvent) => void);
}
export interface ParagraphStyleInterface {
    textAlign?: TextAlign;
    textIndent?: LengthMetrics;
    maxLines?: number;
    overflow?: TextOverflow;
    wordBreak?: WordBreak;
    leadingMargin?: LengthMetrics | LeadingMarginPlaceholder;
    paragraphSpacing?: LengthMetrics;
}
export type StyledStringValue = TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle;
export enum StyledStringKey {
    FONT = 0,
    DECORATION = 1,
    BASELINE_OFFSET = 2,
    LETTER_SPACING = 3,
    TEXT_SHADOW = 4,
    LINE_HEIGHT = 5,
    BACKGROUND_COLOR = 6,
    URL = 7,
    GESTURE = 100,
    PARAGRAPH_STYLE = 200,
    IMAGE = 300,
    CUSTOM_SPAN = 400,
    USER_DATA = 500
}
export interface ResourceImageAttachmentOptions {
    resourceValue: ResourceStr | undefined;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
    colorFilter?: ColorFilterType;
    syncLoad?: boolean;
}
export interface ImageAttachmentInterface {
    value: PixelMap;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
    colorFilter?: ColorFilterType;
}
export type AttachmentType = ImageAttachmentInterface | ResourceImageAttachmentOptions;
export type ColorFilterType = ColorFilter | DrawingColorFilter;
export interface ImageAttachmentLayoutStyle {
    margin?: LengthMetrics | Padding;
    padding?: LengthMetrics | Padding;
    borderRadius?: LengthMetrics | BorderRadiuses;
}
export interface CustomSpanMetrics {
    width: number;
    height?: number;
}
export interface CustomSpanDrawInfo {
    x: number;
    lineTop: number;
    lineBottom: number;
    baseline: number;
}
export interface CustomSpanMeasureInfo {
    fontSize: number;
}
export interface UserDataSpan {
}
export class MutableStyledStringInternal {
    public static fromPtr(ptr: KPointer): MutableStyledString {
        const obj : MutableStyledString = new MutableStyledString()
        obj.peer = new Finalizable(ptr, MutableStyledString.getFinalizer())
        return obj
    }
}
export class MutableStyledString extends StyledString implements MaterializedBase {
    static ctor_mutablestyledstring(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._MutableStyledString_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = MutableStyledString.ctor_mutablestyledstring()
        this.peer = new Finalizable(ctorPtr, MutableStyledString.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._MutableStyledString_getFinalizer()
    }
    public replaceString(start: number, length: number, other: string): void {
        const start_casted = start as (number)
        const length_casted = length as (number)
        const other_casted = other as (string)
        this.replaceString_serialize(start_casted, length_casted, other_casted)
        return
    }
    public insertString(start: number, other: string): void {
        const start_casted = start as (number)
        const other_casted = other as (string)
        this.insertString_serialize(start_casted, other_casted)
        return
    }
    public removeString(start: number, length: number): void {
        const start_casted = start as (number)
        const length_casted = length as (number)
        this.removeString_serialize(start_casted, length_casted)
        return
    }
    public replaceStyle(spanStyle: SpanStyle): void {
        const spanStyle_casted = spanStyle as (SpanStyle)
        this.replaceStyle_serialize(spanStyle_casted)
        return
    }
    public setStyle(spanStyle: SpanStyle): void {
        const spanStyle_casted = spanStyle as (SpanStyle)
        this.setStyle_serialize(spanStyle_casted)
        return
    }
    public removeStyle(start: number, length: number, styledKey: StyledStringKey): void {
        const start_casted = start as (number)
        const length_casted = length as (number)
        const styledKey_casted = styledKey as (StyledStringKey)
        this.removeStyle_serialize(start_casted, length_casted, styledKey_casted)
        return
    }
    public removeStyles(start: number, length: number): void {
        const start_casted = start as (number)
        const length_casted = length as (number)
        this.removeStyles_serialize(start_casted, length_casted)
        return
    }
    public clearStyles(): void {
        this.clearStyles_serialize()
        return
    }
    public replaceStyledString(start: number, length: number, other: StyledString): void {
        const start_casted = start as (number)
        const length_casted = length as (number)
        const other_casted = other as (StyledString)
        this.replaceStyledString_serialize(start_casted, length_casted, other_casted)
        return
    }
    public insertStyledString(start: number, other: StyledString): void {
        const start_casted = start as (number)
        const other_casted = other as (StyledString)
        this.insertStyledString_serialize(start_casted, other_casted)
        return
    }
    public appendStyledString(other: StyledString): void {
        const other_casted = other as (StyledString)
        this.appendStyledString_serialize(other_casted)
        return
    }
    private replaceString_serialize(start: number, length: number, other: string): void {
        ArkUIGeneratedNativeModule._MutableStyledString_replaceString(this.peer!.ptr, start, length, other)
    }
    private insertString_serialize(start: number, other: string): void {
        ArkUIGeneratedNativeModule._MutableStyledString_insertString(this.peer!.ptr, start, other)
    }
    private removeString_serialize(start: number, length: number): void {
        ArkUIGeneratedNativeModule._MutableStyledString_removeString(this.peer!.ptr, start, length)
    }
    private replaceStyle_serialize(spanStyle: SpanStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSpanStyle(spanStyle)
        ArkUIGeneratedNativeModule._MutableStyledString_replaceStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setStyle_serialize(spanStyle: SpanStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSpanStyle(spanStyle)
        ArkUIGeneratedNativeModule._MutableStyledString_setStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeStyle_serialize(start: number, length: number, styledKey: StyledStringKey): void {
        ArkUIGeneratedNativeModule._MutableStyledString_removeStyle(this.peer!.ptr, start, length, TypeChecker.StyledStringKey_ToNumeric(styledKey))
    }
    private removeStyles_serialize(start: number, length: number): void {
        ArkUIGeneratedNativeModule._MutableStyledString_removeStyles(this.peer!.ptr, start, length)
    }
    private clearStyles_serialize(): void {
        ArkUIGeneratedNativeModule._MutableStyledString_clearStyles(this.peer!.ptr)
    }
    private replaceStyledString_serialize(start: number, length: number, other: StyledString): void {
        ArkUIGeneratedNativeModule._MutableStyledString_replaceStyledString(this.peer!.ptr, start, length, toPeerPtr(other))
    }
    private insertStyledString_serialize(start: number, other: StyledString): void {
        ArkUIGeneratedNativeModule._MutableStyledString_insertStyledString(this.peer!.ptr, start, toPeerPtr(other))
    }
    private appendStyledString_serialize(other: StyledString): void {
        ArkUIGeneratedNativeModule._MutableStyledString_appendStyledString(this.peer!.ptr, toPeerPtr(other))
    }
}

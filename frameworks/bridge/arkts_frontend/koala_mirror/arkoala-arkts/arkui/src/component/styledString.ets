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
import { TextBackgroundStyle_serializer, TextBackgroundStyle } from "./span"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { LengthMetrics, LengthMetricsInternal, DrawContext, DrawContextInternal, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { Resource_serializer, Resource } from "./../generated/resource"
import { TextDecorationType, Color, TextDecorationStyle, ImageSpanAlignment, ImageFit, TextAlign, TextOverflow, WordBreak, FontStyle, FontWeight } from "./enums"
import { ResourceColor, SizeOptions_serializer, ColorFilter_serializer, SizeOptions, ColorFilter, ColorFilterInternal, ResourceStr, Padding, BorderRadiuses, Padding_serializer, BorderRadiuses_serializer } from "./units"
import { drawing_ColorFilter_serializer, drawing } from "./../generated/ohos.graphics.drawing"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { LeadingMarginPlaceholder_serializer, LeadingMarginPlaceholder } from "./richEditor"
import { ShadowOptions_serializer, ShadowOptions, ClickEvent, ClickEvent_serializer } from "./common"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { GestureEvent, GestureEvent_serializer } from "./gesture"
export class BackgroundColorStyleInternal {
    public static fromPtr(ptr: KPointer): BackgroundColorStyle {
        return new BackgroundColorStyle(false, ptr)
    }
}
export class BackgroundColorStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly textBackgroundStyle: TextBackgroundStyle
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BackgroundColorStyle.getFinalizer())
        this.textBackgroundStyle = this.getTextBackgroundStyle()
    }
    constructor(textBackgroundStyle: TextBackgroundStyle) {
        this(false, BackgroundColorStyle.construct(textBackgroundStyle))
    }
    static construct(textBackgroundStyle: TextBackgroundStyle): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TextBackgroundStyle_serializer.write(thisSerializer, textBackgroundStyle)
        const retval  = ArkUIGeneratedNativeModule._BackgroundColorStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BackgroundColorStyle_getFinalizer()
    }
    private getTextBackgroundStyle(): TextBackgroundStyle {
        return this.getTextBackgroundStyle_serialize()
    }
    private getTextBackgroundStyle_serialize(): TextBackgroundStyle {
        const retval  = ArkUIGeneratedNativeModule._BackgroundColorStyle_getTextBackgroundStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : TextBackgroundStyle = TextBackgroundStyle_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export class BaselineOffsetStyleInternal {
    public static fromPtr(ptr: KPointer): BaselineOffsetStyle {
        return new BaselineOffsetStyle(false, ptr)
    }
}
export class BaselineOffsetStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly baselineOffset: number
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BaselineOffsetStyle.getFinalizer())
        this.baselineOffset = this.getBaselineOffset()
    }
    constructor(value: LengthMetrics) {
        this(false, BaselineOffsetStyle.construct(value))
    }
    static construct(value: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_construct(toPeerPtr(value))
        return retval
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
export class CustomSpanInternal {
    public static fromPtr(ptr: KPointer): CustomSpan {
        return new CustomSpan(ptr)
    }
}
export class CustomSpan implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get onMeasure(): ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) {
        return this.getOnMeasure()
    }
    set onMeasure(onMeasure: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics)) {
        this.setOnMeasure(onMeasure)
    }
    get onDraw(): ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void) {
        return this.getOnDraw()
    }
    set onDraw(onDraw: ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void)) {
        this.setOnDraw(onDraw)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CustomSpan.getFinalizer())
    }
    constructor() {
        this(CustomSpan.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomSpan_getFinalizer()
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private getOnMeasure(): ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) {
        return this.getOnMeasure_serialize()
    }
    private setOnMeasure(onMeasure: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics)): void {
        const onMeasure_casted = onMeasure as (((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics))
        this.setOnMeasure_serialize(onMeasure_casted)
        return
    }
    private getOnDraw(): ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void) {
        return this.getOnDraw_serialize()
    }
    private setOnDraw(onDraw: ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void)): void {
        const onDraw_casted = onDraw as (((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void))
        this.setOnDraw_serialize(onDraw_casted)
        return
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._CustomSpan_invalidate(this.peer!.ptr)
    }
    private getOnMeasure_serialize(): ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_getOnMeasure(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnMeasure_serialize(onMeasure: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onMeasure)
        ArkUIGeneratedNativeModule._CustomSpan_setOnMeasure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnDraw_serialize(): ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void) {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_getOnDraw(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnDraw_serialize(onDraw: ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onDraw)
        ArkUIGeneratedNativeModule._CustomSpan_setOnDraw(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class DecorationStyleInternal {
    public static fromPtr(ptr: KPointer): DecorationStyle {
        return new DecorationStyle(false, ptr)
    }
}
export class DecorationStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly type: TextDecorationType
    readonly color?: ResourceColor | undefined
    readonly style?: TextDecorationStyle | undefined
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DecorationStyle.getFinalizer())
        this.type = this.getType()
        this.color = this.getColor()
        this.style = this.getStyle()
    }
    constructor(value: DecorationStyleInterface) {
        this(false, DecorationStyle.construct(value))
    }
    static construct(value: DecorationStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        DecorationStyleInterface_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ResourceColor | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__selector : int32 = retvalDeserializer.readInt8()
            let buffer_ : Color | number | string | Resource | undefined
            if (buffer__selector == (0).toChar()) {
                buffer_ = TypeChecker.Color_FromNumeric(retvalDeserializer.readInt32())
            }
            else if (buffer__selector == (1).toChar()) {
                buffer_ = (retvalDeserializer.readNumber() as number)
            }
            else if (buffer__selector == (2).toChar()) {
                buffer_ = (retvalDeserializer.readString() as string)
            }
            else if (buffer__selector == (3).toChar()) {
                buffer_ = Resource_serializer.read(retvalDeserializer)
            }
            else {
                throw new Error("One of the branches for buffer_ has to be chosen through deserialisation.")
            }
            buffer = (buffer_ as Color | number | string | Resource)
        }
        const returnResult : ResourceColor | undefined = buffer
        return returnResult
    }
    private getStyle_serialize(): TextDecorationStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : TextDecorationStyle | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.TextDecorationStyle_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : TextDecorationStyle | undefined = buffer
        return returnResult
    }
}
export class GestureStyleInternal {
    public static fromPtr(ptr: KPointer): GestureStyle {
        return new GestureStyle(false, ptr)
    }
}
export class GestureStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, GestureStyle.getFinalizer())
    }
    constructor(value?: GestureStyleInterface) {
        this(false, GestureStyle.construct(value))
    }
    static construct(value?: GestureStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            GestureStyleInterface_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._GestureStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureStyle_getFinalizer()
    }
}
export class ImageAttachmentInternal {
    public static fromPtr(ptr: KPointer): ImageAttachment {
        return new ImageAttachment(false, ptr)
    }
}
export class ImageAttachment implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly value: image.PixelMap
    readonly size?: SizeOptions | undefined
    readonly verticalAlign?: ImageSpanAlignment | undefined
    readonly objectFit?: ImageFit | undefined
    readonly layoutStyle?: ImageAttachmentLayoutStyle | undefined
    readonly colorFilter?: ColorFilterType | undefined
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ImageAttachment.getFinalizer())
        this.value = this.getValue()
        this.size = this.getSize()
        this.verticalAlign = this.getVerticalAlign()
        this.objectFit = this.getObjectFit()
        this.layoutStyle = this.getLayoutStyle()
        this.colorFilter = this.getColorFilter()
    }
    constructor(value: ImageAttachmentInterface | AttachmentType | undefined) {
        this(false, ImageAttachment.construct(value))
    }
    static construct(value: ImageAttachmentInterface | AttachmentType | undefined): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isImageAttachmentInterface(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as ImageAttachmentInterface
            ImageAttachmentInterface_serializer.write(thisSerializer, value_0)
        }
        else if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as AttachmentType | undefined
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            thisSerializer.writeInt8((value_1_type).toChar())
            if ((value_1_type) != (RuntimeType.UNDEFINED)) {
                const value_1_value  = value_1!
                let value_1_value_type : int32 = RuntimeType.UNDEFINED
                value_1_value_type = runtimeType(value_1_value)
                if (TypeChecker.isImageAttachmentInterface(value_1_value, false, true, true, true, true, true)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_1_value_0  = value_1_value as ImageAttachmentInterface
                    ImageAttachmentInterface_serializer.write(thisSerializer, value_1_value_0)
                }
                else if (TypeChecker.isResourceImageAttachmentOptions(value_1_value, false, true, true, true, true, true, false)) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_1_value_1  = value_1_value as ResourceImageAttachmentOptions
                    ResourceImageAttachmentOptions_serializer.write(thisSerializer, value_1_value_1)
                }
            }
        }
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageAttachment_getFinalizer()
    }
    private getValue(): image.PixelMap {
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
    private getValue_serialize(): image.PixelMap {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getValue(this.peer!.ptr)
        const obj : image.PixelMap = image.PixelMapInternal.fromPtr(retval)
        return obj
    }
    private getSize_serialize(): SizeOptions | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getSize(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : SizeOptions | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = SizeOptions_serializer.read(retvalDeserializer)
        }
        const returnResult : SizeOptions | undefined = buffer
        return returnResult
    }
    private getVerticalAlign_serialize(): ImageSpanAlignment | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getVerticalAlign(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ImageSpanAlignment | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.ImageSpanAlignment_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : ImageSpanAlignment | undefined = buffer
        return returnResult
    }
    private getObjectFit_serialize(): ImageFit | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getObjectFit(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ImageFit | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.ImageFit_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : ImageFit | undefined = buffer
        return returnResult
    }
    private getLayoutStyle_serialize(): ImageAttachmentLayoutStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getLayoutStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ImageAttachmentLayoutStyle | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = ImageAttachmentLayoutStyle_serializer.read(retvalDeserializer)
        }
        const returnResult : ImageAttachmentLayoutStyle | undefined = buffer
        return returnResult
    }
    private getColorFilter_serialize(): ColorFilterType | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getColorFilter(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ColorFilterType | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__selector : int32 = retvalDeserializer.readInt8()
            let buffer_ : ColorFilter | drawing.ColorFilter | undefined
            if (buffer__selector == (0).toChar()) {
                buffer_ = (ColorFilter_serializer.read(retvalDeserializer) as ColorFilter)
            }
            else if (buffer__selector == (1).toChar()) {
                buffer_ = (drawing_ColorFilter_serializer.read(retvalDeserializer) as drawing.ColorFilter)
            }
            else {
                throw new Error("One of the branches for buffer_ has to be chosen through deserialisation.")
            }
            buffer = (buffer_ as ColorFilter | drawing.ColorFilter)
        }
        const returnResult : ColorFilterType | undefined = buffer
        return returnResult
    }
}
export class LetterSpacingStyleInternal {
    public static fromPtr(ptr: KPointer): LetterSpacingStyle {
        return new LetterSpacingStyle(false, ptr)
    }
}
export class LetterSpacingStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly letterSpacing: number
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LetterSpacingStyle.getFinalizer())
        this.letterSpacing = this.getLetterSpacing()
    }
    constructor(value: LengthMetrics) {
        this(false, LetterSpacingStyle.construct(value))
    }
    static construct(value: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_construct(toPeerPtr(value))
        return retval
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
export class LineHeightStyleInternal {
    public static fromPtr(ptr: KPointer): LineHeightStyle {
        return new LineHeightStyle(false, ptr)
    }
}
export class LineHeightStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly lineHeight: number
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LineHeightStyle.getFinalizer())
        this.lineHeight = this.getLineHeight()
    }
    constructor(lineHeight: LengthMetrics) {
        this(false, LineHeightStyle.construct(lineHeight))
    }
    static construct(lineHeight: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_construct(toPeerPtr(lineHeight))
        return retval
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
export class ParagraphStyleInternal {
    public static fromPtr(ptr: KPointer): ParagraphStyle {
        return new ParagraphStyle(false, ptr)
    }
}
export class ParagraphStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly textAlign?: TextAlign | undefined
    readonly textIndent?: number | undefined
    readonly maxLines?: number | undefined
    readonly overflow?: TextOverflow | undefined
    readonly wordBreak?: WordBreak | undefined
    readonly leadingMargin?: number | LeadingMarginPlaceholder | undefined
    readonly paragraphSpacing?: number | undefined
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ParagraphStyle.getFinalizer())
        this.textAlign = this.getTextAlign()
        this.textIndent = this.getTextIndent()
        this.maxLines = this.getMaxLines()
        this.overflow = this.getOverflow()
        this.wordBreak = this.getWordBreak()
        this.leadingMargin = this.getLeadingMargin()
        this.paragraphSpacing = this.getParagraphSpacing()
    }
    constructor(value?: ParagraphStyleInterface) {
        this(false, ParagraphStyle.construct(value))
    }
    static construct(value?: ParagraphStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ParagraphStyleInterface_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : TextAlign | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.TextAlign_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : TextAlign | undefined = buffer
        return returnResult
    }
    private getTextIndent_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getTextIndent(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private getMaxLines_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getMaxLines(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private getOverflow_serialize(): TextOverflow | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getOverflow(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : TextOverflow | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.TextOverflow_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : TextOverflow | undefined = buffer
        return returnResult
    }
    private getWordBreak_serialize(): WordBreak | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getWordBreak(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : WordBreak | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.WordBreak_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : WordBreak | undefined = buffer
        return returnResult
    }
    private getLeadingMargin_serialize(): number | LeadingMarginPlaceholder | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getLeadingMargin(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | LeadingMarginPlaceholder | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__selector : int32 = retvalDeserializer.readInt8()
            let buffer_ : number | LeadingMarginPlaceholder | undefined
            if (buffer__selector == (0).toChar()) {
                buffer_ = (retvalDeserializer.readNumber() as number)
            }
            else if (buffer__selector == (1).toChar()) {
                buffer_ = LeadingMarginPlaceholder_serializer.read(retvalDeserializer)
            }
            else {
                throw new Error("One of the branches for buffer_ has to be chosen through deserialisation.")
            }
            buffer = (buffer_ as number | LeadingMarginPlaceholder)
        }
        const returnResult : number | LeadingMarginPlaceholder | undefined = buffer
        return returnResult
    }
    private getParagraphSpacing_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getParagraphSpacing(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
}
export class StyledStringInternal {
    public static fromPtr(ptr: KPointer): StyledString {
        return new StyledString(false, false, ptr)
    }
}
export class StyledString implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly length: number
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, StyledString.getFinalizer())
        this.length = this.getLength()
    }
    constructor(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>) {
        this(false, false, StyledString.construct(value, styles))
    }
    static construct(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isImageAttachment(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as ImageAttachment
            ImageAttachment_serializer.write(thisSerializer, value_1)
        }
        else if (TypeChecker.isCustomSpan(value, false, false)) {
            thisSerializer.writeInt8((2).toChar())
            const value_2  = value as CustomSpan
            CustomSpan_serializer.write(thisSerializer, value_2)
        }
        let styles_type : int32 = RuntimeType.UNDEFINED
        styles_type = runtimeType(styles)
        thisSerializer.writeInt8((styles_type).toChar())
        if ((styles_type) != (RuntimeType.UNDEFINED)) {
            const styles_value  = styles!
            thisSerializer.writeInt32((styles_value.length).toInt())
            for (let styles_value_counter_i = 0; styles_value_counter_i < styles_value.length; styles_value_counter_i++) {
                const styles_value_element : StyleOptions = styles_value[styles_value_counter_i]
                StyleOptions_serializer.write(thisSerializer, styles_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledString_getFinalizer()
    }
    private static fromHtml_serialize(html: string): Promise<StyledString> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        const retval  = ArkUIGeneratedNativeModule._StyledString_marshalling0(toPeerPtr(styledString), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return new DeserializerBase(retval, retval.length).readBuffer()
    }
    private static unmarshalling0_serialize(buffer: NativeBuffer, callback_: StyledStringUnmarshallCallback): Promise<StyledString> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeBuffer(buffer)
        thisSerializer.holdAndWriteCallback(callback_)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString>()[0]
        ArkUIGeneratedNativeModule._StyledString_unmarshalling0(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static marshalling1_serialize(styledString: StyledString): NativeBuffer {
        const retval  = ArkUIGeneratedNativeModule._StyledString_marshalling1(toPeerPtr(styledString))
        return new DeserializerBase(retval, retval.length).readBuffer()
    }
    private static unmarshalling1_serialize(buffer: NativeBuffer): Promise<StyledString> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeBuffer(buffer)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString>()[0]
        ArkUIGeneratedNativeModule._StyledString_unmarshalling1(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
    public static marshalling(styledString: StyledString, callback_: StyledStringMarshallCallback): NativeBuffer {
        const styledString_casted = styledString as (StyledString)
        const callback__casted = callback_ as (StyledStringMarshallCallback)
        return StyledString.marshalling0_serialize(styledString_casted, callback__casted)
    }
    public static unmarshalling(buffer: NativeBuffer, callback_: StyledStringUnmarshallCallback): Promise<StyledString> {
        const buffer_casted = buffer as (NativeBuffer)
        const callback__casted = callback_ as (StyledStringUnmarshallCallback)
        return StyledString.unmarshalling0_serialize(buffer_casted, callback__casted)
    }
    public static marshalling(styledString: StyledString): NativeBuffer {
        const styledString_casted = styledString as (StyledString)
        return StyledString.marshalling1_serialize(styledString_casted)
    }
    public static unmarshalling(buffer: NativeBuffer): Promise<StyledString> {
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let styledKey_type : int32 = RuntimeType.UNDEFINED
        styledKey_type = runtimeType(styledKey)
        thisSerializer.writeInt8((styledKey_type).toChar())
        if ((styledKey_type) != (RuntimeType.UNDEFINED)) {
            const styledKey_value  = (styledKey as StyledStringKey)
            thisSerializer.writeInt32(TypeChecker.StyledStringKey_ToNumeric(styledKey_value))
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_getStyles(this.peer!.ptr, start, length, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<SpanStyle> = new Array<SpanStyle>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = SpanStyle_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<SpanStyle> = buffer
        return returnResult
    }
    private equals_serialize(other: StyledString): boolean {
        const retval  = ArkUIGeneratedNativeModule._StyledString_equals(this.peer!.ptr, toPeerPtr(other))
        return retval
    }
    private subStyledString_serialize(start: number, length?: number): StyledString {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let length_type : int32 = RuntimeType.UNDEFINED
        length_type = runtimeType(length)
        thisSerializer.writeInt8((length_type).toChar())
        if ((length_type) != (RuntimeType.UNDEFINED)) {
            const length_value  = length!
            thisSerializer.writeNumber(length_value)
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_subStyledString(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : StyledString = StyledStringInternal.fromPtr(retval)
        return obj
    }
    private getLength_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._StyledString_getLength(this.peer!.ptr)
        return retval
    }
}
export class TextShadowStyleInternal {
    public static fromPtr(ptr: KPointer): TextShadowStyle {
        return new TextShadowStyle(false, ptr)
    }
}
export class TextShadowStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly textShadow: Array<ShadowOptions>
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextShadowStyle.getFinalizer())
        this.textShadow = this.getTextShadow()
    }
    constructor(value: ShadowOptions | Array<ShadowOptions>) {
        this(false, TextShadowStyle.construct(value))
    }
    static construct(value: ShadowOptions | Array<ShadowOptions>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isShadowOptions(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as ShadowOptions
            ShadowOptions_serializer.write(thisSerializer, value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_ShadowOptions(value))) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as Array<ShadowOptions>
            thisSerializer.writeInt32((value_1.length).toInt())
            for (let value_1_counter_i = 0; value_1_counter_i < value_1.length; value_1_counter_i++) {
                const value_1_element : ShadowOptions = value_1[value_1_counter_i]
                ShadowOptions_serializer.write(thisSerializer, value_1_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextShadowStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextShadowStyle_getFinalizer()
    }
    private getTextShadow(): Array<ShadowOptions> {
        return this.getTextShadow_serialize()
    }
    private getTextShadow_serialize(): Array<ShadowOptions> {
        const retval  = ArkUIGeneratedNativeModule._TextShadowStyle_getTextShadow(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<ShadowOptions> = new Array<ShadowOptions>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = ShadowOptions_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<ShadowOptions> = buffer
        return returnResult
    }
}
export class TextStyleInternal {
    public static fromPtr(ptr: KPointer): TextStyle {
        return new TextStyle(false, ptr)
    }
}
export class TextStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly fontColor?: ResourceColor | undefined
    readonly fontFamily?: string | undefined
    readonly fontSize?: number | undefined
    readonly fontWeight?: number | undefined
    readonly fontStyle?: FontStyle | undefined
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextStyle.getFinalizer())
        this.fontColor = this.getFontColor()
        this.fontFamily = this.getFontFamily()
        this.fontSize = this.getFontSize()
        this.fontWeight = this.getFontWeight()
        this.fontStyle = this.getFontStyle()
    }
    constructor(value?: TextStyleInterface) {
        this(false, TextStyle.construct(value))
    }
    static construct(value?: TextStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextStyleInterface_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextStyle_getFinalizer()
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
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontColor(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ResourceColor | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__selector : int32 = retvalDeserializer.readInt8()
            let buffer_ : Color | number | string | Resource | undefined
            if (buffer__selector == (0).toChar()) {
                buffer_ = TypeChecker.Color_FromNumeric(retvalDeserializer.readInt32())
            }
            else if (buffer__selector == (1).toChar()) {
                buffer_ = (retvalDeserializer.readNumber() as number)
            }
            else if (buffer__selector == (2).toChar()) {
                buffer_ = (retvalDeserializer.readString() as string)
            }
            else if (buffer__selector == (3).toChar()) {
                buffer_ = Resource_serializer.read(retvalDeserializer)
            }
            else {
                throw new Error("One of the branches for buffer_ has to be chosen through deserialisation.")
            }
            buffer = (buffer_ as Color | number | string | Resource)
        }
        const returnResult : ResourceColor | undefined = buffer
        return returnResult
    }
    private getFontFamily_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontFamily(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : string | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readString() as string)
        }
        const returnResult : string | undefined = buffer
        return returnResult
    }
    private getFontSize_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontSize(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private getFontWeight_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontWeight(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private getFontStyle_serialize(): FontStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : FontStyle | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.FontStyle_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : FontStyle | undefined = buffer
        return returnResult
    }
}
export class UrlStyleInternal {
    public static fromPtr(ptr: KPointer): UrlStyle {
        return new UrlStyle(false, ptr)
    }
}
export class UrlStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    readonly url: string
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, UrlStyle.getFinalizer())
        this.url = this.getUrl()
    }
    constructor(url: string) {
        this(false, UrlStyle.construct(url))
    }
    static construct(url: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UrlStyle_construct(url)
        return retval
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
export class UserDataSpanInternal {
    public static fromPtr(ptr: KPointer): UserDataSpan {
        return new UserDataSpan(ptr)
    }
}
export class UserDataSpan implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, UserDataSpan.getFinalizer())
    }
    constructor() {
        this(UserDataSpan.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UserDataSpan_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UserDataSpan_getFinalizer()
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
    onClick?: ((value0: ClickEvent) => void);
    onLongPress?: ((value0: GestureEvent) => void);
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
    value: image.PixelMap;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
    colorFilter?: ColorFilterType;
}
export type AttachmentType = ImageAttachmentInterface | ResourceImageAttachmentOptions;
export type ColorFilterType = ColorFilter | drawing.ColorFilter;
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
export class GestureStyle_serializer {
    public static write(buffer: SerializerBase, value: GestureStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): GestureStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return GestureStyleInternal.fromPtr(ptr)
    }
}
export class StyledString_serializer {
    public static write(buffer: SerializerBase, value: StyledString): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): StyledString {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return StyledStringInternal.fromPtr(ptr)
    }
}
export class UrlStyle_serializer {
    public static write(buffer: SerializerBase, value: UrlStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): UrlStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return UrlStyleInternal.fromPtr(ptr)
    }
}
export class UserDataSpan_serializer {
    public static write(buffer: SerializerBase, value: UserDataSpan): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): UserDataSpan {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return UserDataSpanInternal.fromPtr(ptr)
    }
}
export class BaselineOffsetStyle_serializer {
    public static write(buffer: SerializerBase, value: BaselineOffsetStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BaselineOffsetStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BaselineOffsetStyleInternal.fromPtr(ptr)
    }
}
export class CustomSpan_serializer {
    public static write(buffer: SerializerBase, value: CustomSpan): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CustomSpan {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CustomSpanInternal.fromPtr(ptr)
    }
}
export class CustomSpanDrawInfo_serializer {
    public static write(buffer: SerializerBase, value: CustomSpanDrawInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_lineTop  = value.lineTop
        valueSerializer.writeNumber(value_lineTop)
        const value_lineBottom  = value.lineBottom
        valueSerializer.writeNumber(value_lineBottom)
        const value_baseline  = value.baseline
        valueSerializer.writeNumber(value_baseline)
    }
    public static read(buffer: DeserializerBase): CustomSpanDrawInfo {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const lineTop_result : number = (valueDeserializer.readNumber() as number)
        const lineBottom_result : number = (valueDeserializer.readNumber() as number)
        const baseline_result : number = (valueDeserializer.readNumber() as number)
        let value : CustomSpanDrawInfo = ({x: x_result, lineTop: lineTop_result, lineBottom: lineBottom_result, baseline: baseline_result} as CustomSpanDrawInfo)
        return value
    }
}
export class CustomSpanMeasureInfo_serializer {
    public static write(buffer: SerializerBase, value: CustomSpanMeasureInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontSize  = value.fontSize
        valueSerializer.writeNumber(value_fontSize)
    }
    public static read(buffer: DeserializerBase): CustomSpanMeasureInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fontSize_result : number = (valueDeserializer.readNumber() as number)
        let value : CustomSpanMeasureInfo = ({fontSize: fontSize_result} as CustomSpanMeasureInfo)
        return value
    }
}
export class CustomSpanMetrics_serializer {
    public static write(buffer: SerializerBase, value: CustomSpanMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            valueSerializer.writeNumber(value_height_value)
        }
    }
    public static read(buffer: DeserializerBase): CustomSpanMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            height_buf = (valueDeserializer.readNumber() as number)
        }
        const height_result : number | undefined = height_buf
        let value : CustomSpanMetrics = ({width: width_result, height: height_result} as CustomSpanMetrics)
        return value
    }
}
export class GestureStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: GestureStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const value_onClick  = value.onClick
        let value_onClick_type : int32 = RuntimeType.UNDEFINED
        value_onClick_type = runtimeType(value_onClick)
        valueSerializer.writeInt8((value_onClick_type).toChar())
        if ((value_onClick_type) != (RuntimeType.UNDEFINED)) {
            const value_onClick_value  = value_onClick!
            valueSerializer.holdAndWriteCallback(value_onClick_value)
        }
        const value_onLongPress  = value.onLongPress
        let value_onLongPress_type : int32 = RuntimeType.UNDEFINED
        value_onLongPress_type = runtimeType(value_onLongPress)
        valueSerializer.writeInt8((value_onLongPress_type).toChar())
        if ((value_onLongPress_type) != (RuntimeType.UNDEFINED)) {
            const value_onLongPress_value  = value_onLongPress!
            valueSerializer.holdAndWriteCallback(value_onLongPress_value)
        }
    }
    public static read(buffer: DeserializerBase): GestureStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const onClick_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onClick_buf : ((value0: ClickEvent) => void) | undefined
        if ((onClick_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onClick_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onClick_buf__call : KPointer = valueDeserializer.readPointer()
            const onClick_buf__callSync : KPointer = valueDeserializer.readPointer()
            onClick_buf = (value0: ClickEvent):void => { 
    const onClick_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onClick_buf__argsSerializer.writeInt32(onClick_buf__resource.resourceId);
    onClick_buf__argsSerializer.writePointer(onClick_buf__call);
    onClick_buf__argsSerializer.writePointer(onClick_buf__callSync);
    ClickEvent_serializer.write(onClick_buf__argsSerializer, value0);
    InteropNativeModule._CallCallback(1097178637, onClick_buf__argsSerializer.asBuffer(), onClick_buf__argsSerializer.length());
    onClick_buf__argsSerializer.release();
    return; }
        }
        const onClick_result : ((value0: ClickEvent) => void) | undefined = onClick_buf
        const onLongPress_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onLongPress_buf : ((value0: GestureEvent) => void) | undefined
        if ((onLongPress_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onLongPress_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onLongPress_buf__call : KPointer = valueDeserializer.readPointer()
            const onLongPress_buf__callSync : KPointer = valueDeserializer.readPointer()
            onLongPress_buf = (value0: GestureEvent):void => { 
    const onLongPress_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onLongPress_buf__argsSerializer.writeInt32(onLongPress_buf__resource.resourceId);
    onLongPress_buf__argsSerializer.writePointer(onLongPress_buf__call);
    onLongPress_buf__argsSerializer.writePointer(onLongPress_buf__callSync);
    GestureEvent_serializer.write(onLongPress_buf__argsSerializer, value0);
    InteropNativeModule._CallCallback(-1143194492, onLongPress_buf__argsSerializer.asBuffer(), onLongPress_buf__argsSerializer.length());
    onLongPress_buf__argsSerializer.release();
    return; }
        }
        const onLongPress_result : ((value0: GestureEvent) => void) | undefined = onLongPress_buf
        let value : GestureStyleInterface = ({onClick: onClick_result, onLongPress: onLongPress_result} as GestureStyleInterface)
        return value
    }
}
export class LetterSpacingStyle_serializer {
    public static write(buffer: SerializerBase, value: LetterSpacingStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LetterSpacingStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LetterSpacingStyleInternal.fromPtr(ptr)
    }
}
export class LineHeightStyle_serializer {
    public static write(buffer: SerializerBase, value: LineHeightStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LineHeightStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LineHeightStyleInternal.fromPtr(ptr)
    }
}
export class MutableStyledString_serializer {
    public static write(buffer: SerializerBase, value: MutableStyledString): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): MutableStyledString {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return MutableStyledStringInternal.fromPtr(ptr)
    }
}
export class TextShadowStyle_serializer {
    public static write(buffer: SerializerBase, value: TextShadowStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextShadowStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextShadowStyleInternal.fromPtr(ptr)
    }
}
export class DecorationStyle_serializer {
    public static write(buffer: SerializerBase, value: DecorationStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DecorationStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DecorationStyleInternal.fromPtr(ptr)
    }
}
export class DecorationStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: DecorationStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.TextDecorationType_ToNumeric(value_type))
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
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as TextDecorationStyle)
            valueSerializer.writeInt32(TypeChecker.TextDecorationStyle_ToNumeric(value_style_value))
        }
    }
    public static read(buffer: DeserializerBase): DecorationStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : TextDecorationType = TypeChecker.TextDecorationType_FromNumeric(valueDeserializer.readInt32())
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
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : TextDecorationStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.TextDecorationStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : TextDecorationStyle | undefined = style_buf
        let value : DecorationStyleInterface = ({type: type_result, color: color_result, style: style_result} as DecorationStyleInterface)
        return value
    }
}
export class TextStyle_serializer {
    public static write(buffer: SerializerBase, value: TextStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextStyleInternal.fromPtr(ptr)
    }
}
export class TextStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: TextStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        valueSerializer.writeInt8((value_fontColor_type).toChar())
        if ((value_fontColor_type) != (RuntimeType.UNDEFINED)) {
            const value_fontColor_value  = value_fontColor!
            let value_fontColor_value_type : int32 = RuntimeType.UNDEFINED
            value_fontColor_value_type = runtimeType(value_fontColor_value)
            if (TypeChecker.isColor(value_fontColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontColor_value_0  = value_fontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_fontColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontColor_value_1  = value_fontColor_value as number
                valueSerializer.writeNumber(value_fontColor_value_1)
            }
            else if (RuntimeType.STRING == value_fontColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontColor_value_2  = value_fontColor_value as string
                valueSerializer.writeString(value_fontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_fontColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_fontColor_value_3  = value_fontColor_value as Resource
                Resource_serializer.write(valueSerializer, value_fontColor_value_3)
            }
        }
        const value_fontFamily  = value.fontFamily
        let value_fontFamily_type : int32 = RuntimeType.UNDEFINED
        value_fontFamily_type = runtimeType(value_fontFamily)
        valueSerializer.writeInt8((value_fontFamily_type).toChar())
        if ((value_fontFamily_type) != (RuntimeType.UNDEFINED)) {
            const value_fontFamily_value  = value_fontFamily!
            let value_fontFamily_value_type : int32 = RuntimeType.UNDEFINED
            value_fontFamily_value_type = runtimeType(value_fontFamily_value)
            if (RuntimeType.STRING == value_fontFamily_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontFamily_value_0  = value_fontFamily_value as string
                valueSerializer.writeString(value_fontFamily_value_0)
            }
            else if (RuntimeType.OBJECT == value_fontFamily_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontFamily_value_1  = value_fontFamily_value as Resource
                Resource_serializer.write(valueSerializer, value_fontFamily_value_1)
            }
        }
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8((value_fontSize_type).toChar())
        if ((value_fontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSize_value  = value_fontSize!
            LengthMetrics_serializer.write(valueSerializer, value_fontSize_value)
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8((value_fontWeight_type).toChar())
        if ((value_fontWeight_type) != (RuntimeType.UNDEFINED)) {
            const value_fontWeight_value  = value_fontWeight!
            let value_fontWeight_value_type : int32 = RuntimeType.UNDEFINED
            value_fontWeight_value_type = runtimeType(value_fontWeight_value)
            if (RuntimeType.NUMBER == value_fontWeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontWeight_value_0  = value_fontWeight_value as number
                valueSerializer.writeNumber(value_fontWeight_value_0)
            }
            else if (TypeChecker.isFontWeight(value_fontWeight_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontWeight_value_1  = value_fontWeight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_fontWeight_value_1))
            }
            else if (RuntimeType.STRING == value_fontWeight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontWeight_value_2  = value_fontWeight_value as string
                valueSerializer.writeString(value_fontWeight_value_2)
            }
        }
        const value_fontStyle  = value.fontStyle
        let value_fontStyle_type : int32 = RuntimeType.UNDEFINED
        value_fontStyle_type = runtimeType(value_fontStyle)
        valueSerializer.writeInt8((value_fontStyle_type).toChar())
        if ((value_fontStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_fontStyle_value  = (value_fontStyle as FontStyle)
            valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_fontStyle_value))
        }
    }
    public static read(buffer: DeserializerBase): TextStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const fontColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontColor_buf : ResourceColor | undefined
        if ((fontColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontColor_buf__selector : int32 = valueDeserializer.readInt8()
            let fontColor_buf_ : Color | number | string | Resource | undefined
            if (fontColor_buf__selector == (0).toChar()) {
                fontColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontColor_buf__selector == (1).toChar()) {
                fontColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontColor_buf__selector == (2).toChar()) {
                fontColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontColor_buf__selector == (3).toChar()) {
                fontColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontColor_buf_ has to be chosen through deserialisation.")
            }
            fontColor_buf = (fontColor_buf_ as Color | number | string | Resource)
        }
        const fontColor_result : ResourceColor | undefined = fontColor_buf
        const fontFamily_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamily_buf : ResourceStr | undefined
        if ((fontFamily_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontFamily_buf__selector : int32 = valueDeserializer.readInt8()
            let fontFamily_buf_ : string | Resource | undefined
            if (fontFamily_buf__selector == (0).toChar()) {
                fontFamily_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontFamily_buf__selector == (1).toChar()) {
                fontFamily_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontFamily_buf_ has to be chosen through deserialisation.")
            }
            fontFamily_buf = (fontFamily_buf_ as string | Resource)
        }
        const fontFamily_result : ResourceStr | undefined = fontFamily_buf
        const fontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSize_buf : LengthMetrics | undefined
        if ((fontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontSize_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const fontSize_result : LengthMetrics | undefined = fontSize_buf
        const fontWeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeight_buf : number | FontWeight | string | undefined
        if ((fontWeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontWeight_buf__selector : int32 = valueDeserializer.readInt8()
            let fontWeight_buf_ : number | FontWeight | string | undefined
            if (fontWeight_buf__selector == (0).toChar()) {
                fontWeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontWeight_buf__selector == (1).toChar()) {
                fontWeight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontWeight_buf__selector == (2).toChar()) {
                fontWeight_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for fontWeight_buf_ has to be chosen through deserialisation.")
            }
            fontWeight_buf = (fontWeight_buf_ as number | FontWeight | string)
        }
        const fontWeight_result : number | FontWeight | string | undefined = fontWeight_buf
        const fontStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyle_buf : FontStyle | undefined
        if ((fontStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontStyle_buf = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const fontStyle_result : FontStyle | undefined = fontStyle_buf
        let value : TextStyleInterface = ({fontColor: fontColor_result, fontFamily: fontFamily_result, fontSize: fontSize_result, fontWeight: fontWeight_result, fontStyle: fontStyle_result} as TextStyleInterface)
        return value
    }
}
export class ImageAttachmentLayoutStyle_serializer {
    public static write(buffer: SerializerBase, value: ImageAttachmentLayoutStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8((value_margin_type).toChar())
        if ((value_margin_type) != (RuntimeType.UNDEFINED)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (TypeChecker.isLengthMetrics(value_margin_value, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_margin_value_0  = value_margin_value as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, value_margin_value_0)
            }
            else if (TypeChecker.isPadding(value_margin_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_margin_value_1  = value_margin_value as Padding
                Padding_serializer.write(valueSerializer, value_margin_value_1)
            }
        }
        const value_padding  = value.padding
        let value_padding_type : int32 = RuntimeType.UNDEFINED
        value_padding_type = runtimeType(value_padding)
        valueSerializer.writeInt8((value_padding_type).toChar())
        if ((value_padding_type) != (RuntimeType.UNDEFINED)) {
            const value_padding_value  = value_padding!
            let value_padding_value_type : int32 = RuntimeType.UNDEFINED
            value_padding_value_type = runtimeType(value_padding_value)
            if (TypeChecker.isLengthMetrics(value_padding_value, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_padding_value_0  = value_padding_value as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, value_padding_value_0)
            }
            else if (TypeChecker.isPadding(value_padding_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_padding_value_1  = value_padding_value as Padding
                Padding_serializer.write(valueSerializer, value_padding_value_1)
            }
        }
        const value_borderRadius  = value.borderRadius
        let value_borderRadius_type : int32 = RuntimeType.UNDEFINED
        value_borderRadius_type = runtimeType(value_borderRadius)
        valueSerializer.writeInt8((value_borderRadius_type).toChar())
        if ((value_borderRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_borderRadius_value  = value_borderRadius!
            let value_borderRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_borderRadius_value_type = runtimeType(value_borderRadius_value)
            if (TypeChecker.isLengthMetrics(value_borderRadius_value, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderRadius_value_0  = value_borderRadius_value as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, value_borderRadius_value_0)
            }
            else if (TypeChecker.isBorderRadiuses(value_borderRadius_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderRadius_value_1  = value_borderRadius_value as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, value_borderRadius_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ImageAttachmentLayoutStyle {
        let valueDeserializer : DeserializerBase = buffer
        const margin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let margin_buf : LengthMetrics | Padding | undefined
        if ((margin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : LengthMetrics | Padding | undefined
            if (margin_buf__selector == (0).toChar()) {
                margin_buf_ = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            else if (margin_buf__selector == (1).toChar()) {
                margin_buf_ = Padding_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as LengthMetrics | Padding)
        }
        const margin_result : LengthMetrics | Padding | undefined = margin_buf
        const padding_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let padding_buf : LengthMetrics | Padding | undefined
        if ((padding_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const padding_buf__selector : int32 = valueDeserializer.readInt8()
            let padding_buf_ : LengthMetrics | Padding | undefined
            if (padding_buf__selector == (0).toChar()) {
                padding_buf_ = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            else if (padding_buf__selector == (1).toChar()) {
                padding_buf_ = Padding_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for padding_buf_ has to be chosen through deserialisation.")
            }
            padding_buf = (padding_buf_ as LengthMetrics | Padding)
        }
        const padding_result : LengthMetrics | Padding | undefined = padding_buf
        const borderRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadius_buf : LengthMetrics | BorderRadiuses | undefined
        if ((borderRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let borderRadius_buf_ : LengthMetrics | BorderRadiuses | undefined
            if (borderRadius_buf__selector == (0).toChar()) {
                borderRadius_buf_ = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            else if (borderRadius_buf__selector == (1).toChar()) {
                borderRadius_buf_ = BorderRadiuses_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderRadius_buf_ has to be chosen through deserialisation.")
            }
            borderRadius_buf = (borderRadius_buf_ as LengthMetrics | BorderRadiuses)
        }
        const borderRadius_result : LengthMetrics | BorderRadiuses | undefined = borderRadius_buf
        let value : ImageAttachmentLayoutStyle = ({margin: margin_result, padding: padding_result, borderRadius: borderRadius_result} as ImageAttachmentLayoutStyle)
        return value
    }
}
export class ParagraphStyle_serializer {
    public static write(buffer: SerializerBase, value: ParagraphStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ParagraphStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ParagraphStyleInternal.fromPtr(ptr)
    }
}
export class ParagraphStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: ParagraphStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const value_textAlign  = value.textAlign
        let value_textAlign_type : int32 = RuntimeType.UNDEFINED
        value_textAlign_type = runtimeType(value_textAlign)
        valueSerializer.writeInt8((value_textAlign_type).toChar())
        if ((value_textAlign_type) != (RuntimeType.UNDEFINED)) {
            const value_textAlign_value  = (value_textAlign as TextAlign)
            valueSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(value_textAlign_value))
        }
        const value_textIndent  = value.textIndent
        let value_textIndent_type : int32 = RuntimeType.UNDEFINED
        value_textIndent_type = runtimeType(value_textIndent)
        valueSerializer.writeInt8((value_textIndent_type).toChar())
        if ((value_textIndent_type) != (RuntimeType.UNDEFINED)) {
            const value_textIndent_value  = value_textIndent!
            LengthMetrics_serializer.write(valueSerializer, value_textIndent_value)
        }
        const value_maxLines  = value.maxLines
        let value_maxLines_type : int32 = RuntimeType.UNDEFINED
        value_maxLines_type = runtimeType(value_maxLines)
        valueSerializer.writeInt8((value_maxLines_type).toChar())
        if ((value_maxLines_type) != (RuntimeType.UNDEFINED)) {
            const value_maxLines_value  = value_maxLines!
            valueSerializer.writeNumber(value_maxLines_value)
        }
        const value_overflow  = value.overflow
        let value_overflow_type : int32 = RuntimeType.UNDEFINED
        value_overflow_type = runtimeType(value_overflow)
        valueSerializer.writeInt8((value_overflow_type).toChar())
        if ((value_overflow_type) != (RuntimeType.UNDEFINED)) {
            const value_overflow_value  = (value_overflow as TextOverflow)
            valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow_value))
        }
        const value_wordBreak  = value.wordBreak
        let value_wordBreak_type : int32 = RuntimeType.UNDEFINED
        value_wordBreak_type = runtimeType(value_wordBreak)
        valueSerializer.writeInt8((value_wordBreak_type).toChar())
        if ((value_wordBreak_type) != (RuntimeType.UNDEFINED)) {
            const value_wordBreak_value  = (value_wordBreak as WordBreak)
            valueSerializer.writeInt32(TypeChecker.WordBreak_ToNumeric(value_wordBreak_value))
        }
        const value_leadingMargin  = value.leadingMargin
        let value_leadingMargin_type : int32 = RuntimeType.UNDEFINED
        value_leadingMargin_type = runtimeType(value_leadingMargin)
        valueSerializer.writeInt8((value_leadingMargin_type).toChar())
        if ((value_leadingMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_leadingMargin_value  = value_leadingMargin!
            let value_leadingMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_leadingMargin_value_type = runtimeType(value_leadingMargin_value)
            if (TypeChecker.isLengthMetrics(value_leadingMargin_value, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_leadingMargin_value_0  = value_leadingMargin_value as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, value_leadingMargin_value_0)
            }
            else if (TypeChecker.isLeadingMarginPlaceholder(value_leadingMargin_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_leadingMargin_value_1  = value_leadingMargin_value as LeadingMarginPlaceholder
                LeadingMarginPlaceholder_serializer.write(valueSerializer, value_leadingMargin_value_1)
            }
        }
        const value_paragraphSpacing  = value.paragraphSpacing
        let value_paragraphSpacing_type : int32 = RuntimeType.UNDEFINED
        value_paragraphSpacing_type = runtimeType(value_paragraphSpacing)
        valueSerializer.writeInt8((value_paragraphSpacing_type).toChar())
        if ((value_paragraphSpacing_type) != (RuntimeType.UNDEFINED)) {
            const value_paragraphSpacing_value  = value_paragraphSpacing!
            LengthMetrics_serializer.write(valueSerializer, value_paragraphSpacing_value)
        }
    }
    public static read(buffer: DeserializerBase): ParagraphStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const textAlign_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textAlign_buf : TextAlign | undefined
        if ((textAlign_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textAlign_buf = TypeChecker.TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const textAlign_result : TextAlign | undefined = textAlign_buf
        const textIndent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textIndent_buf : LengthMetrics | undefined
        if ((textIndent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textIndent_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const textIndent_result : LengthMetrics | undefined = textIndent_buf
        const maxLines_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLines_buf : number | undefined
        if ((maxLines_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxLines_buf = (valueDeserializer.readNumber() as number)
        }
        const maxLines_result : number | undefined = maxLines_buf
        const overflow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflow_buf : TextOverflow | undefined
        if ((overflow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            overflow_buf = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        }
        const overflow_result : TextOverflow | undefined = overflow_buf
        const wordBreak_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreak_buf : WordBreak | undefined
        if ((wordBreak_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            wordBreak_buf = TypeChecker.WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreak_result : WordBreak | undefined = wordBreak_buf
        const leadingMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leadingMargin_buf : LengthMetrics | LeadingMarginPlaceholder | undefined
        if ((leadingMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const leadingMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let leadingMargin_buf_ : LengthMetrics | LeadingMarginPlaceholder | undefined
            if (leadingMargin_buf__selector == (0).toChar()) {
                leadingMargin_buf_ = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            else if (leadingMargin_buf__selector == (1).toChar()) {
                leadingMargin_buf_ = LeadingMarginPlaceholder_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for leadingMargin_buf_ has to be chosen through deserialisation.")
            }
            leadingMargin_buf = (leadingMargin_buf_ as LengthMetrics | LeadingMarginPlaceholder)
        }
        const leadingMargin_result : LengthMetrics | LeadingMarginPlaceholder | undefined = leadingMargin_buf
        const paragraphSpacing_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paragraphSpacing_buf : LengthMetrics | undefined
        if ((paragraphSpacing_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            paragraphSpacing_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const paragraphSpacing_result : LengthMetrics | undefined = paragraphSpacing_buf
        let value : ParagraphStyleInterface = ({textAlign: textAlign_result, textIndent: textIndent_result, maxLines: maxLines_result, overflow: overflow_result, wordBreak: wordBreak_result, leadingMargin: leadingMargin_result, paragraphSpacing: paragraphSpacing_result} as ParagraphStyleInterface)
        return value
    }
}
export class BackgroundColorStyle_serializer {
    public static write(buffer: SerializerBase, value: BackgroundColorStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BackgroundColorStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BackgroundColorStyleInternal.fromPtr(ptr)
    }
}
export class ImageAttachment_serializer {
    public static write(buffer: SerializerBase, value: ImageAttachment): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ImageAttachment {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ImageAttachmentInternal.fromPtr(ptr)
    }
}
export class ImageAttachmentInterface_serializer {
    public static write(buffer: SerializerBase, value: ImageAttachmentInterface): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        image_PixelMap_serializer.write(valueSerializer, value_value)
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8((value_size_type).toChar())
        if ((value_size_type) != (RuntimeType.UNDEFINED)) {
            const value_size_value  = value_size!
            SizeOptions_serializer.write(valueSerializer, value_size_value)
        }
        const value_verticalAlign  = value.verticalAlign
        let value_verticalAlign_type : int32 = RuntimeType.UNDEFINED
        value_verticalAlign_type = runtimeType(value_verticalAlign)
        valueSerializer.writeInt8((value_verticalAlign_type).toChar())
        if ((value_verticalAlign_type) != (RuntimeType.UNDEFINED)) {
            const value_verticalAlign_value  = (value_verticalAlign as ImageSpanAlignment)
            valueSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(value_verticalAlign_value))
        }
        const value_objectFit  = value.objectFit
        let value_objectFit_type : int32 = RuntimeType.UNDEFINED
        value_objectFit_type = runtimeType(value_objectFit)
        valueSerializer.writeInt8((value_objectFit_type).toChar())
        if ((value_objectFit_type) != (RuntimeType.UNDEFINED)) {
            const value_objectFit_value  = (value_objectFit as ImageFit)
            valueSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_objectFit_value))
        }
        const value_layoutStyle  = value.layoutStyle
        let value_layoutStyle_type : int32 = RuntimeType.UNDEFINED
        value_layoutStyle_type = runtimeType(value_layoutStyle)
        valueSerializer.writeInt8((value_layoutStyle_type).toChar())
        if ((value_layoutStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_layoutStyle_value  = value_layoutStyle!
            ImageAttachmentLayoutStyle_serializer.write(valueSerializer, value_layoutStyle_value)
        }
        const value_colorFilter  = value.colorFilter
        let value_colorFilter_type : int32 = RuntimeType.UNDEFINED
        value_colorFilter_type = runtimeType(value_colorFilter)
        valueSerializer.writeInt8((value_colorFilter_type).toChar())
        if ((value_colorFilter_type) != (RuntimeType.UNDEFINED)) {
            const value_colorFilter_value  = value_colorFilter!
            let value_colorFilter_value_type : int32 = RuntimeType.UNDEFINED
            value_colorFilter_value_type = runtimeType(value_colorFilter_value)
            if (TypeChecker.isColorFilter(value_colorFilter_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_colorFilter_value_0  = value_colorFilter_value as ColorFilter
                ColorFilter_serializer.write(valueSerializer, value_colorFilter_value_0)
            }
            else if (TypeChecker.isdrawing_ColorFilter(value_colorFilter_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_colorFilter_value_1  = value_colorFilter_value as drawing.ColorFilter
                drawing_ColorFilter_serializer.write(valueSerializer, value_colorFilter_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ImageAttachmentInterface {
        let valueDeserializer : DeserializerBase = buffer
        const value_result : image.PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        const size_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let size_buf : SizeOptions | undefined
        if ((size_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            size_buf = SizeOptions_serializer.read(valueDeserializer)
        }
        const size_result : SizeOptions | undefined = size_buf
        const verticalAlign_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let verticalAlign_buf : ImageSpanAlignment | undefined
        if ((verticalAlign_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            verticalAlign_buf = TypeChecker.ImageSpanAlignment_FromNumeric(valueDeserializer.readInt32())
        }
        const verticalAlign_result : ImageSpanAlignment | undefined = verticalAlign_buf
        const objectFit_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let objectFit_buf : ImageFit | undefined
        if ((objectFit_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            objectFit_buf = TypeChecker.ImageFit_FromNumeric(valueDeserializer.readInt32())
        }
        const objectFit_result : ImageFit | undefined = objectFit_buf
        const layoutStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let layoutStyle_buf : ImageAttachmentLayoutStyle | undefined
        if ((layoutStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            layoutStyle_buf = ImageAttachmentLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyle_result : ImageAttachmentLayoutStyle | undefined = layoutStyle_buf
        const colorFilter_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorFilter_buf : ColorFilterType | undefined
        if ((colorFilter_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const colorFilter_buf__selector : int32 = valueDeserializer.readInt8()
            let colorFilter_buf_ : ColorFilter | drawing.ColorFilter | undefined
            if (colorFilter_buf__selector == (0).toChar()) {
                colorFilter_buf_ = (ColorFilter_serializer.read(valueDeserializer) as ColorFilter)
            }
            else if (colorFilter_buf__selector == (1).toChar()) {
                colorFilter_buf_ = (drawing_ColorFilter_serializer.read(valueDeserializer) as drawing.ColorFilter)
            }
            else {
                throw new Error("One of the branches for colorFilter_buf_ has to be chosen through deserialisation.")
            }
            colorFilter_buf = (colorFilter_buf_ as ColorFilter | drawing.ColorFilter)
        }
        const colorFilter_result : ColorFilterType | undefined = colorFilter_buf
        let value : ImageAttachmentInterface = ({value: value_result, size: size_result, verticalAlign: verticalAlign_result, objectFit: objectFit_result, layoutStyle: layoutStyle_result, colorFilter: colorFilter_result} as ImageAttachmentInterface)
        return value
    }
}
export class ResourceImageAttachmentOptions_serializer {
    public static write(buffer: SerializerBase, value: ResourceImageAttachmentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_resourceValue  = value.resourceValue
        let value_resourceValue_type : int32 = RuntimeType.UNDEFINED
        value_resourceValue_type = runtimeType(value_resourceValue)
        valueSerializer.writeInt8((value_resourceValue_type).toChar())
        if ((value_resourceValue_type) != (RuntimeType.UNDEFINED)) {
            const value_resourceValue_value  = value_resourceValue!
            let value_resourceValue_value_type : int32 = RuntimeType.UNDEFINED
            value_resourceValue_value_type = runtimeType(value_resourceValue_value)
            if (RuntimeType.STRING == value_resourceValue_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_resourceValue_value_0  = value_resourceValue_value as string
                valueSerializer.writeString(value_resourceValue_value_0)
            }
            else if (RuntimeType.OBJECT == value_resourceValue_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_resourceValue_value_1  = value_resourceValue_value as Resource
                Resource_serializer.write(valueSerializer, value_resourceValue_value_1)
            }
        }
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8((value_size_type).toChar())
        if ((value_size_type) != (RuntimeType.UNDEFINED)) {
            const value_size_value  = value_size!
            SizeOptions_serializer.write(valueSerializer, value_size_value)
        }
        const value_verticalAlign  = value.verticalAlign
        let value_verticalAlign_type : int32 = RuntimeType.UNDEFINED
        value_verticalAlign_type = runtimeType(value_verticalAlign)
        valueSerializer.writeInt8((value_verticalAlign_type).toChar())
        if ((value_verticalAlign_type) != (RuntimeType.UNDEFINED)) {
            const value_verticalAlign_value  = (value_verticalAlign as ImageSpanAlignment)
            valueSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(value_verticalAlign_value))
        }
        const value_objectFit  = value.objectFit
        let value_objectFit_type : int32 = RuntimeType.UNDEFINED
        value_objectFit_type = runtimeType(value_objectFit)
        valueSerializer.writeInt8((value_objectFit_type).toChar())
        if ((value_objectFit_type) != (RuntimeType.UNDEFINED)) {
            const value_objectFit_value  = (value_objectFit as ImageFit)
            valueSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_objectFit_value))
        }
        const value_layoutStyle  = value.layoutStyle
        let value_layoutStyle_type : int32 = RuntimeType.UNDEFINED
        value_layoutStyle_type = runtimeType(value_layoutStyle)
        valueSerializer.writeInt8((value_layoutStyle_type).toChar())
        if ((value_layoutStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_layoutStyle_value  = value_layoutStyle!
            ImageAttachmentLayoutStyle_serializer.write(valueSerializer, value_layoutStyle_value)
        }
        const value_colorFilter  = value.colorFilter
        let value_colorFilter_type : int32 = RuntimeType.UNDEFINED
        value_colorFilter_type = runtimeType(value_colorFilter)
        valueSerializer.writeInt8((value_colorFilter_type).toChar())
        if ((value_colorFilter_type) != (RuntimeType.UNDEFINED)) {
            const value_colorFilter_value  = value_colorFilter!
            let value_colorFilter_value_type : int32 = RuntimeType.UNDEFINED
            value_colorFilter_value_type = runtimeType(value_colorFilter_value)
            if (TypeChecker.isColorFilter(value_colorFilter_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_colorFilter_value_0  = value_colorFilter_value as ColorFilter
                ColorFilter_serializer.write(valueSerializer, value_colorFilter_value_0)
            }
            else if (TypeChecker.isdrawing_ColorFilter(value_colorFilter_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_colorFilter_value_1  = value_colorFilter_value as drawing.ColorFilter
                drawing_ColorFilter_serializer.write(valueSerializer, value_colorFilter_value_1)
            }
        }
        const value_syncLoad  = value.syncLoad
        let value_syncLoad_type : int32 = RuntimeType.UNDEFINED
        value_syncLoad_type = runtimeType(value_syncLoad)
        valueSerializer.writeInt8((value_syncLoad_type).toChar())
        if ((value_syncLoad_type) != (RuntimeType.UNDEFINED)) {
            const value_syncLoad_value  = value_syncLoad!
            valueSerializer.writeBoolean(value_syncLoad_value)
        }
    }
    public static read(buffer: DeserializerBase): ResourceImageAttachmentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const resourceValue_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let resourceValue_buf : ResourceStr | undefined
        if ((resourceValue_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const resourceValue_buf__selector : int32 = valueDeserializer.readInt8()
            let resourceValue_buf_ : string | Resource | undefined
            if (resourceValue_buf__selector == (0).toChar()) {
                resourceValue_buf_ = (valueDeserializer.readString() as string)
            }
            else if (resourceValue_buf__selector == (1).toChar()) {
                resourceValue_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for resourceValue_buf_ has to be chosen through deserialisation.")
            }
            resourceValue_buf = (resourceValue_buf_ as string | Resource)
        }
        const resourceValue_result : ResourceStr | undefined = resourceValue_buf
        const size_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let size_buf : SizeOptions | undefined
        if ((size_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            size_buf = SizeOptions_serializer.read(valueDeserializer)
        }
        const size_result : SizeOptions | undefined = size_buf
        const verticalAlign_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let verticalAlign_buf : ImageSpanAlignment | undefined
        if ((verticalAlign_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            verticalAlign_buf = TypeChecker.ImageSpanAlignment_FromNumeric(valueDeserializer.readInt32())
        }
        const verticalAlign_result : ImageSpanAlignment | undefined = verticalAlign_buf
        const objectFit_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let objectFit_buf : ImageFit | undefined
        if ((objectFit_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            objectFit_buf = TypeChecker.ImageFit_FromNumeric(valueDeserializer.readInt32())
        }
        const objectFit_result : ImageFit | undefined = objectFit_buf
        const layoutStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let layoutStyle_buf : ImageAttachmentLayoutStyle | undefined
        if ((layoutStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            layoutStyle_buf = ImageAttachmentLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyle_result : ImageAttachmentLayoutStyle | undefined = layoutStyle_buf
        const colorFilter_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorFilter_buf : ColorFilterType | undefined
        if ((colorFilter_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const colorFilter_buf__selector : int32 = valueDeserializer.readInt8()
            let colorFilter_buf_ : ColorFilter | drawing.ColorFilter | undefined
            if (colorFilter_buf__selector == (0).toChar()) {
                colorFilter_buf_ = (ColorFilter_serializer.read(valueDeserializer) as ColorFilter)
            }
            else if (colorFilter_buf__selector == (1).toChar()) {
                colorFilter_buf_ = (drawing_ColorFilter_serializer.read(valueDeserializer) as drawing.ColorFilter)
            }
            else {
                throw new Error("One of the branches for colorFilter_buf_ has to be chosen through deserialisation.")
            }
            colorFilter_buf = (colorFilter_buf_ as ColorFilter | drawing.ColorFilter)
        }
        const colorFilter_result : ColorFilterType | undefined = colorFilter_buf
        const syncLoad_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let syncLoad_buf : boolean | undefined
        if ((syncLoad_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            syncLoad_buf = valueDeserializer.readBoolean()
        }
        const syncLoad_result : boolean | undefined = syncLoad_buf
        let value : ResourceImageAttachmentOptions = ({resourceValue: resourceValue_result, size: size_result, verticalAlign: verticalAlign_result, objectFit: objectFit_result, layoutStyle: layoutStyle_result, colorFilter: colorFilter_result, syncLoad: syncLoad_result} as ResourceImageAttachmentOptions)
        return value
    }
}
export class StyleOptions_serializer {
    public static write(buffer: SerializerBase, value: StyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_length  = value.length
        let value_length_type : int32 = RuntimeType.UNDEFINED
        value_length_type = runtimeType(value_length)
        valueSerializer.writeInt8((value_length_type).toChar())
        if ((value_length_type) != (RuntimeType.UNDEFINED)) {
            const value_length_value  = value_length!
            valueSerializer.writeNumber(value_length_value)
        }
        const value_styledKey  = value.styledKey
        valueSerializer.writeInt32(TypeChecker.StyledStringKey_ToNumeric(value_styledKey))
        const value_styledValue  = value.styledValue
        let value_styledValue_type : int32 = RuntimeType.UNDEFINED
        value_styledValue_type = runtimeType(value_styledValue)
        if (TypeChecker.isTextStyle(value_styledValue, false, false, false, false, false)) {
            valueSerializer.writeInt8((0).toChar())
            const value_styledValue_0  = value_styledValue as TextStyle
            TextStyle_serializer.write(valueSerializer, value_styledValue_0)
        }
        else if (TypeChecker.isDecorationStyle(value_styledValue, false, false, false)) {
            valueSerializer.writeInt8((1).toChar())
            const value_styledValue_1  = value_styledValue as DecorationStyle
            DecorationStyle_serializer.write(valueSerializer, value_styledValue_1)
        }
        else if (TypeChecker.isBaselineOffsetStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_styledValue_2  = value_styledValue as BaselineOffsetStyle
            BaselineOffsetStyle_serializer.write(valueSerializer, value_styledValue_2)
        }
        else if (TypeChecker.isLetterSpacingStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((3).toChar())
            const value_styledValue_3  = value_styledValue as LetterSpacingStyle
            LetterSpacingStyle_serializer.write(valueSerializer, value_styledValue_3)
        }
        else if (TypeChecker.isTextShadowStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((4).toChar())
            const value_styledValue_4  = value_styledValue as TextShadowStyle
            TextShadowStyle_serializer.write(valueSerializer, value_styledValue_4)
        }
        else if (TypeChecker.isGestureStyle(value_styledValue)) {
            valueSerializer.writeInt8((5).toChar())
            const value_styledValue_5  = value_styledValue as GestureStyle
            GestureStyle_serializer.write(valueSerializer, value_styledValue_5)
        }
        else if (TypeChecker.isImageAttachment(value_styledValue, false, false, false, false, false, false)) {
            valueSerializer.writeInt8((6).toChar())
            const value_styledValue_6  = value_styledValue as ImageAttachment
            ImageAttachment_serializer.write(valueSerializer, value_styledValue_6)
        }
        else if (TypeChecker.isParagraphStyle(value_styledValue, false, false, false, false, false, false, false)) {
            valueSerializer.writeInt8((7).toChar())
            const value_styledValue_7  = value_styledValue as ParagraphStyle
            ParagraphStyle_serializer.write(valueSerializer, value_styledValue_7)
        }
        else if (TypeChecker.isLineHeightStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((8).toChar())
            const value_styledValue_8  = value_styledValue as LineHeightStyle
            LineHeightStyle_serializer.write(valueSerializer, value_styledValue_8)
        }
        else if (TypeChecker.isUrlStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((9).toChar())
            const value_styledValue_9  = value_styledValue as UrlStyle
            UrlStyle_serializer.write(valueSerializer, value_styledValue_9)
        }
        else if (TypeChecker.isCustomSpan(value_styledValue, false, false)) {
            valueSerializer.writeInt8((10).toChar())
            const value_styledValue_10  = value_styledValue as CustomSpan
            CustomSpan_serializer.write(valueSerializer, value_styledValue_10)
        }
        else if (TypeChecker.isUserDataSpan(value_styledValue)) {
            valueSerializer.writeInt8((11).toChar())
            const value_styledValue_11  = value_styledValue as UserDataSpan
            UserDataSpan_serializer.write(valueSerializer, value_styledValue_11)
        }
        else if (TypeChecker.isBackgroundColorStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((12).toChar())
            const value_styledValue_12  = value_styledValue as BackgroundColorStyle
            BackgroundColorStyle_serializer.write(valueSerializer, value_styledValue_12)
        }
    }
    public static read(buffer: DeserializerBase): StyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : number | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const length_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let length_buf : number | undefined
        if ((length_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            length_buf = (valueDeserializer.readNumber() as number)
        }
        const length_result : number | undefined = length_buf
        const styledKey_result : StyledStringKey = TypeChecker.StyledStringKey_FromNumeric(valueDeserializer.readInt32())
        const styledValue_buf_selector : int32 = valueDeserializer.readInt8()
        let styledValue_buf : TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle | undefined
        if (styledValue_buf_selector == (0).toChar()) {
            styledValue_buf = (TextStyle_serializer.read(valueDeserializer) as TextStyle)
        }
        else if (styledValue_buf_selector == (1).toChar()) {
            styledValue_buf = (DecorationStyle_serializer.read(valueDeserializer) as DecorationStyle)
        }
        else if (styledValue_buf_selector == (2).toChar()) {
            styledValue_buf = (BaselineOffsetStyle_serializer.read(valueDeserializer) as BaselineOffsetStyle)
        }
        else if (styledValue_buf_selector == (3).toChar()) {
            styledValue_buf = (LetterSpacingStyle_serializer.read(valueDeserializer) as LetterSpacingStyle)
        }
        else if (styledValue_buf_selector == (4).toChar()) {
            styledValue_buf = (TextShadowStyle_serializer.read(valueDeserializer) as TextShadowStyle)
        }
        else if (styledValue_buf_selector == (5).toChar()) {
            styledValue_buf = (GestureStyle_serializer.read(valueDeserializer) as GestureStyle)
        }
        else if (styledValue_buf_selector == (6).toChar()) {
            styledValue_buf = (ImageAttachment_serializer.read(valueDeserializer) as ImageAttachment)
        }
        else if (styledValue_buf_selector == (7).toChar()) {
            styledValue_buf = (ParagraphStyle_serializer.read(valueDeserializer) as ParagraphStyle)
        }
        else if (styledValue_buf_selector == (8).toChar()) {
            styledValue_buf = (LineHeightStyle_serializer.read(valueDeserializer) as LineHeightStyle)
        }
        else if (styledValue_buf_selector == (9).toChar()) {
            styledValue_buf = (UrlStyle_serializer.read(valueDeserializer) as UrlStyle)
        }
        else if (styledValue_buf_selector == (10).toChar()) {
            styledValue_buf = (CustomSpan_serializer.read(valueDeserializer) as CustomSpan)
        }
        else if (styledValue_buf_selector == (11).toChar()) {
            styledValue_buf = (UserDataSpan_serializer.read(valueDeserializer) as UserDataSpan)
        }
        else if (styledValue_buf_selector == (12).toChar()) {
            styledValue_buf = (BackgroundColorStyle_serializer.read(valueDeserializer) as BackgroundColorStyle)
        }
        else {
            throw new Error("One of the branches for styledValue_buf has to be chosen through deserialisation.")
        }
        const styledValue_result : StyledStringValue = (styledValue_buf as TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle)
        let value : StyleOptions = ({start: start_result, length: length_result, styledKey: styledKey_result, styledValue: styledValue_result} as StyleOptions)
        return value
    }
}
export class SpanStyle_serializer {
    public static write(buffer: SerializerBase, value: SpanStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        valueSerializer.writeNumber(value_start)
        const value_length  = value.length
        valueSerializer.writeNumber(value_length)
        const value_styledKey  = value.styledKey
        valueSerializer.writeInt32(TypeChecker.StyledStringKey_ToNumeric(value_styledKey))
        const value_styledValue  = value.styledValue
        let value_styledValue_type : int32 = RuntimeType.UNDEFINED
        value_styledValue_type = runtimeType(value_styledValue)
        if (TypeChecker.isTextStyle(value_styledValue, false, false, false, false, false)) {
            valueSerializer.writeInt8((0).toChar())
            const value_styledValue_0  = value_styledValue as TextStyle
            TextStyle_serializer.write(valueSerializer, value_styledValue_0)
        }
        else if (TypeChecker.isDecorationStyle(value_styledValue, false, false, false)) {
            valueSerializer.writeInt8((1).toChar())
            const value_styledValue_1  = value_styledValue as DecorationStyle
            DecorationStyle_serializer.write(valueSerializer, value_styledValue_1)
        }
        else if (TypeChecker.isBaselineOffsetStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_styledValue_2  = value_styledValue as BaselineOffsetStyle
            BaselineOffsetStyle_serializer.write(valueSerializer, value_styledValue_2)
        }
        else if (TypeChecker.isLetterSpacingStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((3).toChar())
            const value_styledValue_3  = value_styledValue as LetterSpacingStyle
            LetterSpacingStyle_serializer.write(valueSerializer, value_styledValue_3)
        }
        else if (TypeChecker.isTextShadowStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((4).toChar())
            const value_styledValue_4  = value_styledValue as TextShadowStyle
            TextShadowStyle_serializer.write(valueSerializer, value_styledValue_4)
        }
        else if (TypeChecker.isGestureStyle(value_styledValue)) {
            valueSerializer.writeInt8((5).toChar())
            const value_styledValue_5  = value_styledValue as GestureStyle
            GestureStyle_serializer.write(valueSerializer, value_styledValue_5)
        }
        else if (TypeChecker.isImageAttachment(value_styledValue, false, false, false, false, false, false)) {
            valueSerializer.writeInt8((6).toChar())
            const value_styledValue_6  = value_styledValue as ImageAttachment
            ImageAttachment_serializer.write(valueSerializer, value_styledValue_6)
        }
        else if (TypeChecker.isParagraphStyle(value_styledValue, false, false, false, false, false, false, false)) {
            valueSerializer.writeInt8((7).toChar())
            const value_styledValue_7  = value_styledValue as ParagraphStyle
            ParagraphStyle_serializer.write(valueSerializer, value_styledValue_7)
        }
        else if (TypeChecker.isLineHeightStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((8).toChar())
            const value_styledValue_8  = value_styledValue as LineHeightStyle
            LineHeightStyle_serializer.write(valueSerializer, value_styledValue_8)
        }
        else if (TypeChecker.isUrlStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((9).toChar())
            const value_styledValue_9  = value_styledValue as UrlStyle
            UrlStyle_serializer.write(valueSerializer, value_styledValue_9)
        }
        else if (TypeChecker.isCustomSpan(value_styledValue, false, false)) {
            valueSerializer.writeInt8((10).toChar())
            const value_styledValue_10  = value_styledValue as CustomSpan
            CustomSpan_serializer.write(valueSerializer, value_styledValue_10)
        }
        else if (TypeChecker.isUserDataSpan(value_styledValue)) {
            valueSerializer.writeInt8((11).toChar())
            const value_styledValue_11  = value_styledValue as UserDataSpan
            UserDataSpan_serializer.write(valueSerializer, value_styledValue_11)
        }
        else if (TypeChecker.isBackgroundColorStyle(value_styledValue, false)) {
            valueSerializer.writeInt8((12).toChar())
            const value_styledValue_12  = value_styledValue as BackgroundColorStyle
            BackgroundColorStyle_serializer.write(valueSerializer, value_styledValue_12)
        }
    }
    public static read(buffer: DeserializerBase): SpanStyle {
        let valueDeserializer : DeserializerBase = buffer
        const start_result : number = (valueDeserializer.readNumber() as number)
        const length_result : number = (valueDeserializer.readNumber() as number)
        const styledKey_result : StyledStringKey = TypeChecker.StyledStringKey_FromNumeric(valueDeserializer.readInt32())
        const styledValue_buf_selector : int32 = valueDeserializer.readInt8()
        let styledValue_buf : TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle | undefined
        if (styledValue_buf_selector == (0).toChar()) {
            styledValue_buf = (TextStyle_serializer.read(valueDeserializer) as TextStyle)
        }
        else if (styledValue_buf_selector == (1).toChar()) {
            styledValue_buf = (DecorationStyle_serializer.read(valueDeserializer) as DecorationStyle)
        }
        else if (styledValue_buf_selector == (2).toChar()) {
            styledValue_buf = (BaselineOffsetStyle_serializer.read(valueDeserializer) as BaselineOffsetStyle)
        }
        else if (styledValue_buf_selector == (3).toChar()) {
            styledValue_buf = (LetterSpacingStyle_serializer.read(valueDeserializer) as LetterSpacingStyle)
        }
        else if (styledValue_buf_selector == (4).toChar()) {
            styledValue_buf = (TextShadowStyle_serializer.read(valueDeserializer) as TextShadowStyle)
        }
        else if (styledValue_buf_selector == (5).toChar()) {
            styledValue_buf = (GestureStyle_serializer.read(valueDeserializer) as GestureStyle)
        }
        else if (styledValue_buf_selector == (6).toChar()) {
            styledValue_buf = (ImageAttachment_serializer.read(valueDeserializer) as ImageAttachment)
        }
        else if (styledValue_buf_selector == (7).toChar()) {
            styledValue_buf = (ParagraphStyle_serializer.read(valueDeserializer) as ParagraphStyle)
        }
        else if (styledValue_buf_selector == (8).toChar()) {
            styledValue_buf = (LineHeightStyle_serializer.read(valueDeserializer) as LineHeightStyle)
        }
        else if (styledValue_buf_selector == (9).toChar()) {
            styledValue_buf = (UrlStyle_serializer.read(valueDeserializer) as UrlStyle)
        }
        else if (styledValue_buf_selector == (10).toChar()) {
            styledValue_buf = (CustomSpan_serializer.read(valueDeserializer) as CustomSpan)
        }
        else if (styledValue_buf_selector == (11).toChar()) {
            styledValue_buf = (UserDataSpan_serializer.read(valueDeserializer) as UserDataSpan)
        }
        else if (styledValue_buf_selector == (12).toChar()) {
            styledValue_buf = (BackgroundColorStyle_serializer.read(valueDeserializer) as BackgroundColorStyle)
        }
        else {
            throw new Error("One of the branches for styledValue_buf has to be chosen through deserialisation.")
        }
        const styledValue_result : StyledStringValue = (styledValue_buf as TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle)
        let value : SpanStyle = ({start: start_result, length: length_result, styledKey: styledKey_result, styledValue: styledValue_result} as SpanStyle)
        return value
    }
}
export class MutableStyledStringInternal {
    public static fromPtr(ptr: KPointer): MutableStyledString {
        return new MutableStyledString(false, false, ptr)
    }
}
export class MutableStyledString extends StyledString implements MaterializedBase {
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        super(false, false, peerPtr)
    }
    constructor(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>) {
        this(false, false, MutableStyledString.construct(value, styles))
    }
    static construct(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isImageAttachment(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as ImageAttachment
            ImageAttachment_serializer.write(thisSerializer, value_1)
        }
        else if (TypeChecker.isCustomSpan(value, false, false)) {
            thisSerializer.writeInt8((2).toChar())
            const value_2  = value as CustomSpan
            CustomSpan_serializer.write(thisSerializer, value_2)
        }
        let styles_type : int32 = RuntimeType.UNDEFINED
        styles_type = runtimeType(styles)
        thisSerializer.writeInt8((styles_type).toChar())
        if ((styles_type) != (RuntimeType.UNDEFINED)) {
            const styles_value  = styles!
            thisSerializer.writeInt32((styles_value.length).toInt())
            for (let styles_value_counter_i = 0; styles_value_counter_i < styles_value.length; styles_value_counter_i++) {
                const styles_value_element : StyleOptions = styles_value[styles_value_counter_i]
                StyleOptions_serializer.write(thisSerializer, styles_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._MutableStyledString_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SpanStyle_serializer.write(thisSerializer, spanStyle)
        ArkUIGeneratedNativeModule._MutableStyledString_replaceStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setStyle_serialize(spanStyle: SpanStyle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SpanStyle_serializer.write(thisSerializer, spanStyle)
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

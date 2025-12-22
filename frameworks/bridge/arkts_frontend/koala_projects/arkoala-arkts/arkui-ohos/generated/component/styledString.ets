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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, resourceFinalizerRegister, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { TextBackgroundStyle_serializer, TextBackgroundStyle } from './span'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { arkui_Graphics_LengthMetrics_serializer, arkui_Graphics_DrawContext_serializer } from './../framework/Graphics'
import { LengthMetrics as arkui_component_units_LengthMetrics, ResourceColor, Resource as arkui_component_units_Resource, SizeOptions_serializer, ColorFilter_serializer, SizeOptions, ColorFilter, ColorFilterInternal, ResourceStr as arkui_component_units_ResourceStr, Margin, Padding, BorderRadiuses, Padding_serializer, BorderRadiuses_serializer } from './units'
import { LengthMetrics as arkui_Graphics_LengthMetrics, DrawContext as arkui_Graphics_DrawContext } from '@arkui.Graphics'
import { extractors } from '#handwritten'
import { global_resource_Resource_serializer } from './../framework/resource'
import { TextDecorationType, Color as arkui_component_enums_Color, TextDecorationStyle, ImageSpanAlignment, ImageFit, TextAlign, TextOverflow, WordBreak, FontStyle, FontWeight } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { drawing_ColorFilter_serializer } from './../framework/ohos.graphics.drawing'
import { PixelMap, ShadowOptions_serializer, ShadowOptions, ClickEvent, Callback as arkui_component_common_Callback, ClickEvent_serializer } from './common'
import { default as image } from '@ohos.multimedia.image'
import { DrawingColorFilter } from './image'
import { default as drawing } from '@ohos.graphics.drawing'
import { LeadingMarginPlaceholder_serializer, LeadingMarginPlaceholder } from './richEditor'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { GestureEvent, GestureEvent_serializer } from './gesture'
import { image_PixelMap_serializer } from './../framework/ohos.multimedia.image'
export class BackgroundColorStyleInternal {
    public static fromPtr(ptr: KPointer): BackgroundColorStyle {
        return new BackgroundColorStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class BackgroundColorStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly textBackgroundStyle: TextBackgroundStyle
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BackgroundColorStyle.getFinalizer())
        this.textBackgroundStyle = this.getTextBackgroundStyle()
    }
    constructor(textBackgroundStyle: TextBackgroundStyle) {
        this(MaterializedBaseTag.NOP, BackgroundColorStyle.construct(textBackgroundStyle))
        this.textBackgroundStyle = this.getTextBackgroundStyle()
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
        return new BaselineOffsetStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class BaselineOffsetStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly baselineOffset: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BaselineOffsetStyle.getFinalizer())
        this.baselineOffset = this.getBaselineOffset()
    }
    constructor(value: arkui_component_units_LengthMetrics) {
        this(MaterializedBaseTag.NOP, BaselineOffsetStyle.construct(value))
        this.baselineOffset = this.getBaselineOffset()
    }
    static construct(value: arkui_component_units_LengthMetrics): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaselineOffsetStyle_getFinalizer()
    }
    private getBaselineOffset(): double {
        return this.getBaselineOffset_serialize()
    }
    private getBaselineOffset_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_getBaselineOffset(this.peer!.ptr)
        return retval
    }
}
export class CustomSpanInternal {
    public static fromPtr(ptr: KPointer): CustomSpan {
        return new CustomSpan(MaterializedBaseTag.NOP, ptr)
    }
}
export class CustomSpan implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
        throw new Error('Not implemented!')
    }
    get onMeasure_callback(): ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) {
        return this.getOnMeasure_callback()
    }
    set onMeasure_callback(onMeasure_callback: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics)) {
        this.setOnMeasure_callback(onMeasure_callback)
    }
    onDraw(context: arkui_Graphics_DrawContext, drawInfo: CustomSpanDrawInfo): void {
        throw new Error('Not implemented!')
    }
    get onDraw_callback(): ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void) {
        return this.getOnDraw_callback()
    }
    set onDraw_callback(onDraw_callback: ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void)) {
        this.setOnDraw_callback(onDraw_callback)
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CustomSpan.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, CustomSpan.construct())
        this.onMeasure_callback = this.onMeasure
        this.onDraw_callback = this.onDraw
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
    private getOnMeasure_callback(): ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) {
        return this.getOnMeasure_callback_serialize()
    }
    private setOnMeasure_callback(onMeasure_callback: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics)): void {
        const onMeasure_callback_casted = onMeasure_callback as (((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics))
        this.setOnMeasure_callback_serialize(onMeasure_callback_casted)
        return
    }
    private getOnDraw_callback(): ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void) {
        return this.getOnDraw_callback_serialize()
    }
    private setOnDraw_callback(onDraw_callback: ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void)): void {
        const onDraw_callback_casted = onDraw_callback as (((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void))
        this.setOnDraw_callback_serialize(onDraw_callback_casted)
        return
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._CustomSpan_invalidate(this.peer!.ptr)
    }
    private getOnMeasure_callback_serialize(): ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_getOnMeasure_callback(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferBufResource : CallbackResource = retvalDeserializer.readCallbackResource()
        const bufferBufCall : KPointer = retvalDeserializer.readPointer()
        const bufferBufCallSync : KPointer = retvalDeserializer.readPointer()
        const bufferClosure  = (measureInfo: CustomSpanMeasureInfo):CustomSpanMetrics => {
            const bufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
            bufferBufArgsSerializer.writeInt32(bufferBufResource.resourceId);
            bufferBufArgsSerializer.writePointer(bufferBufCall);
            bufferBufArgsSerializer.writePointer(bufferBufCallSync);
            CustomSpanMeasureInfo_serializer.write(bufferBufArgsSerializer, measureInfo);
            let bufferBufContinuationValue : CustomSpanMetrics | undefined;
            const bufferBufContinuationCallback : ((value: CustomSpanMetrics) => void) = (value: CustomSpanMetrics):void => {
            bufferBufContinuationValue = value;
        }
            bufferBufArgsSerializer.holdAndWriteCallback(bufferBufContinuationCallback);
            InteropNativeModule._CallCallbackSync(10, -1570631366, bufferBufArgsSerializer.asBuffer(), bufferBufArgsSerializer.length());
            bufferBufArgsSerializer.release();
            return (bufferBufContinuationValue as CustomSpanMetrics);
        }
        resourceFinalizerRegister(bufferClosure, bufferBufResource)
        const returnResult : ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics) = bufferClosure
        return returnResult
    }
    private setOnMeasure_callback_serialize(onMeasure_callback: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onMeasure_callback)
        ArkUIGeneratedNativeModule._CustomSpan_setOnMeasure_callback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnDraw_callback_serialize(): ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void) {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_getOnDraw_callback(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferBufResource : CallbackResource = retvalDeserializer.readCallbackResource()
        const bufferBufCall : KPointer = retvalDeserializer.readPointer()
        const bufferBufCallSync : KPointer = retvalDeserializer.readPointer()
        const bufferClosure  = (context: arkui_Graphics_DrawContext, drawInfo: CustomSpanDrawInfo):void => {
            const bufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
            bufferBufArgsSerializer.writeInt32(bufferBufResource.resourceId);
            bufferBufArgsSerializer.writePointer(bufferBufCall);
            bufferBufArgsSerializer.writePointer(bufferBufCallSync);
            arkui_Graphics_DrawContext_serializer.write(bufferBufArgsSerializer, context);
            CustomSpanDrawInfo_serializer.write(bufferBufArgsSerializer, drawInfo);
            InteropNativeModule._CallCallbackSync(10, 799028158, bufferBufArgsSerializer.asBuffer(), bufferBufArgsSerializer.length());
            bufferBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(bufferClosure, bufferBufResource)
        const returnResult : ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void) = bufferClosure
        return returnResult
    }
    private setOnDraw_callback_serialize(onDraw_callback: ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onDraw_callback)
        ArkUIGeneratedNativeModule._CustomSpan_setOnDraw_callback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class DecorationStyleInternal {
    public static fromPtr(ptr: KPointer): DecorationStyle {
        return new DecorationStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class DecorationStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly type: TextDecorationType
    public readonly color?: ResourceColor | undefined
    public readonly style?: TextDecorationStyle | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DecorationStyle.getFinalizer())
        this.type = this.getType()
        this.color = this.getColor()
        this.style = this.getStyle()
    }
    constructor(value: DecorationStyleInterface) {
        this(MaterializedBaseTag.NOP, DecorationStyle.construct(value))
        this.type = this.getType()
        this.color = this.getColor()
        this.style = this.getStyle()
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
        return TextDecorationType.fromValue(retval)
    }
    private getColor_serialize(): ResourceColor | undefined {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getColor(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ResourceColor | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptUnionSelector : int32 = retvalDeserializer.readInt8()
            let bufferOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (bufferOptUnionSelector == (0).toByte()) {
                bufferOpt = arkui_component_enums_Color.values()[retvalDeserializer.readInt32()]
            } else if (bufferOptUnionSelector == (1).toByte()) {
                bufferOpt = retvalDeserializer.readInt32()
            } else if (bufferOptUnionSelector == (2).toByte()) {
                bufferOpt = (retvalDeserializer.readString() as string)
            } else if (bufferOptUnionSelector == (3).toByte()) {
                bufferOpt = global_resource_Resource_serializer.read(retvalDeserializer)
            } else {
                throw new Error('One of the branches for bufferOpt has to be chosen through deserialisation.')
            }
            buffer = (bufferOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const returnResult : ResourceColor | undefined = buffer
        return returnResult
    }
    private getStyle_serialize(): TextDecorationStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : TextDecorationStyle | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = TextDecorationStyle.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : TextDecorationStyle | undefined = buffer
        return returnResult
    }
}
export class GestureStyleInternal {
    public static fromPtr(ptr: KPointer): GestureStyle {
        return new GestureStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class GestureStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, GestureStyle.getFinalizer())
    }
    constructor(value?: GestureStyleInterface) {
        this(MaterializedBaseTag.NOP, GestureStyle.construct(value))
    }
    static construct(value?: GestureStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            GestureStyleInterface_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return new ImageAttachment(MaterializedBaseTag.NOP, ptr)
    }
}
export class ImageAttachment implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly value: PixelMap
    public readonly size?: SizeOptions | undefined
    public readonly verticalAlign?: ImageSpanAlignment | undefined
    public readonly objectFit?: ImageFit | undefined
    public readonly layoutStyle?: ImageAttachmentLayoutStyle | undefined
    public readonly colorFilter?: ColorFilterType | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ImageAttachment.getFinalizer())
        this.value = this.getValue()
        this.size = this.getSize()
        this.verticalAlign = this.getVerticalAlign()
        this.objectFit = this.getObjectFit()
        this.layoutStyle = this.getLayoutStyle()
        this.colorFilter = this.getColorFilter()
    }
    constructor(value: AttachmentType | undefined) {
        this(MaterializedBaseTag.NOP, ImageAttachment.construct(value))
        this.value = this.getValue()
        this.size = this.getSize()
        this.verticalAlign = this.getVerticalAlign()
        this.objectFit = this.getObjectFit()
        this.layoutStyle = this.getLayoutStyle()
        this.colorFilter = this.getColorFilter()
    }
    static construct(value: AttachmentType | undefined): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ImageAttachmentInterface) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ImageAttachmentInterface
                ImageAttachmentInterface_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof ResourceImageAttachmentOptions) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as ResourceImageAttachmentOptions
                ResourceImageAttachmentOptions_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
        // instructive change start
        const obj : image.PixelMap = extractors.fromImagePixelMapPtr(retval)
        return obj
        // instructive change end
    }
    private getSize_serialize(): SizeOptions | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getSize(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : SizeOptions | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = SizeOptions_serializer.read(retvalDeserializer)
        }
        const returnResult : SizeOptions | undefined = buffer
        return returnResult
    }
    private getVerticalAlign_serialize(): ImageSpanAlignment | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getVerticalAlign(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ImageSpanAlignment | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = ImageSpanAlignment.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : ImageSpanAlignment | undefined = buffer
        return returnResult
    }
    private getObjectFit_serialize(): ImageFit | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getObjectFit(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ImageFit | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = ImageFit.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : ImageFit | undefined = buffer
        return returnResult
    }
    private getLayoutStyle_serialize(): ImageAttachmentLayoutStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getLayoutStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ImageAttachmentLayoutStyle | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = ImageAttachmentLayoutStyle_serializer.read(retvalDeserializer)
        }
        const returnResult : ImageAttachmentLayoutStyle | undefined = buffer
        return returnResult
    }
    private getColorFilter_serialize(): ColorFilterType | undefined {
        const retval  = ArkUIGeneratedNativeModule._ImageAttachment_getColorFilter(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ColorFilterType | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptUnionSelector : int32 = retvalDeserializer.readInt8()
            let bufferOpt : ColorFilter | DrawingColorFilter | undefined
            if (bufferOptUnionSelector == (0).toByte()) {
                bufferOpt = (ColorFilter_serializer.read(retvalDeserializer) as ColorFilter)
            } else if (bufferOptUnionSelector == (1).toByte()) {
                bufferOpt = (drawing_ColorFilter_serializer.read(retvalDeserializer) as drawing.ColorFilter)
            } else {
                throw new Error('One of the branches for bufferOpt has to be chosen through deserialisation.')
            }
            buffer = (bufferOpt as ColorFilter | DrawingColorFilter)
        }
        const returnResult : ColorFilterType | undefined = buffer
        return returnResult
    }
}
export class LetterSpacingStyleInternal {
    public static fromPtr(ptr: KPointer): LetterSpacingStyle {
        return new LetterSpacingStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class LetterSpacingStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly letterSpacing: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LetterSpacingStyle.getFinalizer())
        this.letterSpacing = this.getLetterSpacing()
    }
    constructor(value: arkui_component_units_LengthMetrics) {
        this(MaterializedBaseTag.NOP, LetterSpacingStyle.construct(value))
        this.letterSpacing = this.getLetterSpacing()
    }
    static construct(value: arkui_component_units_LengthMetrics): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LetterSpacingStyle_getFinalizer()
    }
    private getLetterSpacing(): double {
        return this.getLetterSpacing_serialize()
    }
    private getLetterSpacing_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_getLetterSpacing(this.peer!.ptr)
        return retval
    }
}
export class LineHeightStyleInternal {
    public static fromPtr(ptr: KPointer): LineHeightStyle {
        return new LineHeightStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class LineHeightStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly lineHeight: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LineHeightStyle.getFinalizer())
        this.lineHeight = this.getLineHeight()
    }
    constructor(lineHeight: arkui_component_units_LengthMetrics) {
        this(MaterializedBaseTag.NOP, LineHeightStyle.construct(lineHeight))
        this.lineHeight = this.getLineHeight()
    }
    static construct(lineHeight: arkui_component_units_LengthMetrics): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, lineHeight)
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LineHeightStyle_getFinalizer()
    }
    private getLineHeight(): double {
        return this.getLineHeight_serialize()
    }
    private getLineHeight_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_getLineHeight(this.peer!.ptr)
        return retval
    }
}
export class ParagraphStyleInternal {
    public static fromPtr(ptr: KPointer): ParagraphStyle {
        return new ParagraphStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class ParagraphStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly textAlign?: TextAlign | undefined
    public readonly textIndent?: double | undefined
    public readonly maxLines?: int32 | undefined
    public readonly overflow?: TextOverflow | undefined
    public readonly wordBreak?: WordBreak | undefined
    public readonly leadingMargin?: double | LeadingMarginPlaceholder | undefined
    public readonly paragraphSpacing?: double | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
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
        this(MaterializedBaseTag.NOP, ParagraphStyle.construct(value))
        this.textAlign = this.getTextAlign()
        this.textIndent = this.getTextIndent()
        this.maxLines = this.getMaxLines()
        this.overflow = this.getOverflow()
        this.wordBreak = this.getWordBreak()
        this.leadingMargin = this.getLeadingMargin()
        this.paragraphSpacing = this.getParagraphSpacing()
    }
    static construct(value?: ParagraphStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ParagraphStyleInterface_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
    private getTextIndent(): double | undefined {
        return this.getTextIndent_serialize()
    }
    private getMaxLines(): int32 | undefined {
        return this.getMaxLines_serialize()
    }
    private getOverflow(): TextOverflow | undefined {
        return this.getOverflow_serialize()
    }
    private getWordBreak(): WordBreak | undefined {
        return this.getWordBreak_serialize()
    }
    private getLeadingMargin(): double | LeadingMarginPlaceholder | undefined {
        return this.getLeadingMargin_serialize()
    }
    private getParagraphSpacing(): double | undefined {
        return this.getParagraphSpacing_serialize()
    }
    private getTextAlign_serialize(): TextAlign | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getTextAlign(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : TextAlign | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = TextAlign.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : TextAlign | undefined = buffer
        return returnResult
    }
    private getTextIndent_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getTextIndent(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private getMaxLines_serialize(): int32 | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getMaxLines(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private getOverflow_serialize(): TextOverflow | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getOverflow(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : TextOverflow | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = TextOverflow.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : TextOverflow | undefined = buffer
        return returnResult
    }
    private getWordBreak_serialize(): WordBreak | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getWordBreak(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : WordBreak | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = WordBreak.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : WordBreak | undefined = buffer
        return returnResult
    }
    private getLeadingMargin_serialize(): double | LeadingMarginPlaceholder | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getLeadingMargin(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : double | LeadingMarginPlaceholder | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptUnionSelector : int32 = retvalDeserializer.readInt8()
            let bufferOpt : double | LeadingMarginPlaceholder | undefined
            if (bufferOptUnionSelector == (0).toByte()) {
                bufferOpt = retvalDeserializer.readFloat64()
            } else if (bufferOptUnionSelector == (1).toByte()) {
                bufferOpt = LeadingMarginPlaceholder_serializer.read(retvalDeserializer)
            } else {
                throw new Error('One of the branches for bufferOpt has to be chosen through deserialisation.')
            }
            buffer = (bufferOpt as double | LeadingMarginPlaceholder)
        }
        const returnResult : double | LeadingMarginPlaceholder | undefined = buffer
        return returnResult
    }
    private getParagraphSpacing_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getParagraphSpacing(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
}
export class StyledStringInternal {
    public static fromPtr(ptr: KPointer): StyledString {
        return new StyledString(MaterializedBaseTag.NOP, ptr)
    }
}
export class StyledString implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get length(): int32 {
        return this.getLength()
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, StyledString.getFinalizer())
    }
    constructor(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>) {
        this(MaterializedBaseTag.NOP, StyledString.construct(value, styles))
    }
    static construct(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as string
            thisSerializer.writeString(valueForIdx0)
        } else if (value instanceof ImageAttachment) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as ImageAttachment
            ImageAttachment_serializer.write(thisSerializer, valueForIdx1)
        } else if (value instanceof CustomSpan) {
            thisSerializer.writeInt8((2).toByte())
            const valueForIdx2  = value as CustomSpan
            CustomSpan_serializer.write(thisSerializer, valueForIdx2)
        }
        if (styles !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const stylesTmpValue  = styles!
            thisSerializer.writeInt32((stylesTmpValue.length).toInt())
            for (let stylesTmpValueCounterI = 0; stylesTmpValueCounterI < stylesTmpValue.length; stylesTmpValueCounterI++) {
                const stylesTmpValueTmpElement : StyleOptions = stylesTmpValue[stylesTmpValueCounterI]
                StyleOptions_serializer.write(thisSerializer, stylesTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledString_getFinalizer()
    }
    public static fromHtml(html: string): Promise<StyledString | undefined> {
        const html_casted = html as (string)
        return StyledString.fromHtml_serialize(html_casted)
    }
    public static toHtml(styledString: StyledString): string {
        const styledString_casted = styledString as (StyledString)
        return StyledString.toHtml_serialize(styledString_casted)
    }
    public static marshalling(styledString: StyledString, callback_: StyledStringMarshallCallback): ArrayBuffer | undefined {
        const styledString_casted = styledString as (StyledString)
        const callback__casted = callback_ as (StyledStringMarshallCallback)
        return StyledString.marshalling0_serialize(styledString_casted, callback__casted)
    }
    public static unmarshalling(buffer: ArrayBuffer, callback_: StyledStringUnmarshallCallback): Promise<StyledString | undefined> {
        const buffer_casted = buffer as (ArrayBuffer)
        const callback__casted = callback_ as (StyledStringUnmarshallCallback)
        return StyledString.unmarshalling0_serialize(buffer_casted, callback__casted)
    }
    public static marshalling(styledString: StyledString): ArrayBuffer | undefined {
        const styledString_casted = styledString as (StyledString)
        return StyledString.marshalling1_serialize(styledString_casted)
    }
    public static unmarshalling(buffer: ArrayBuffer): Promise<StyledString | undefined> {
        const buffer_casted = buffer as (ArrayBuffer)
        return StyledString.unmarshalling1_serialize(buffer_casted)
    }
    private static fromHtml_serialize(html: string): Promise<StyledString | undefined> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString | undefined>()[0]
        ArkUIGeneratedNativeModule._StyledString_fromHtml(html, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static toHtml_serialize(styledString: StyledString): string {
        const retval  = ArkUIGeneratedNativeModule._StyledString_toHtml(toPeerPtr(styledString))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static marshalling0_serialize(styledString: StyledString, callback_: StyledStringMarshallCallback): ArrayBuffer | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        const retval  = ArkUIGeneratedNativeModule._StyledString_marshalling0(toPeerPtr(styledString), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ArrayBuffer | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readBuffer() as ArrayBuffer)
        }
        const returnResult : ArrayBuffer | undefined = buffer
        return returnResult
    }
    private static unmarshalling0_serialize(buffer: ArrayBuffer, callback_: StyledStringUnmarshallCallback): Promise<StyledString | undefined> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeBuffer(buffer)
        thisSerializer.holdAndWriteCallback(callback_)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString | undefined>()[0]
        ArkUIGeneratedNativeModule._StyledString_unmarshalling0(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static marshalling1_serialize(styledString: StyledString): ArrayBuffer | undefined {
        const retval  = ArkUIGeneratedNativeModule._StyledString_marshalling1(toPeerPtr(styledString))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ArrayBuffer | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readBuffer() as ArrayBuffer)
        }
        const returnResult : ArrayBuffer | undefined = buffer
        return returnResult
    }
    private static unmarshalling1_serialize(buffer: ArrayBuffer): Promise<StyledString | undefined> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeBuffer(buffer)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<StyledString | undefined>()[0]
        ArkUIGeneratedNativeModule._StyledString_unmarshalling1(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public getString(): string {
        return this.getString_serialize()
    }
    public getStyles(start: int32, length: int32, styledKey?: StyledStringKey): Array<SpanStyle> | undefined {
        const start_casted = start as (int32)
        const length_casted = length as (int32)
        const styledKey_casted = styledKey as (StyledStringKey | undefined)
        return this.getStyles_serialize(start_casted, length_casted, styledKey_casted)
    }
    public equals(other: StyledString): boolean {
        const other_casted = other as (StyledString)
        return this.equals_serialize(other_casted)
    }
    public subStyledString(start: int32, length?: int32): StyledString | undefined {
        const start_casted = start as (int32)
        const length_casted = length as (int32 | undefined)
        return this.subStyledString_serialize(start_casted, length_casted)
    }
    private getLength(): int32 {
        return this.getLength_serialize()
    }
    private getString_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._StyledString_getString(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getStyles_serialize(start: int32, length: int32, styledKey?: StyledStringKey): Array<SpanStyle> | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (styledKey !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styledKeyTmpValue  = (styledKey as StyledStringKey)
            thisSerializer.writeInt32(styledKeyTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_getStyles(this.peer!.ptr, start, length, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : Array<SpanStyle> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength : int32 = retvalDeserializer.readInt32()
            let bufferOpt : Array<SpanStyle> = new Array<SpanStyle>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = SpanStyle_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult : Array<SpanStyle> | undefined = buffer
        return returnResult
    }
    private equals_serialize(other: StyledString): boolean {
        const retval  = ArkUIGeneratedNativeModule._StyledString_equals(this.peer!.ptr, toPeerPtr(other))
        return retval
    }
    private subStyledString_serialize(start: int32, length?: int32): StyledString | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (length !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const lengthTmpValue  = length!
            thisSerializer.writeInt32(lengthTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._StyledString_subStyledString(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : StyledString | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (StyledString_serializer.read(retvalDeserializer) as StyledString)
        }
        const returnResult : StyledString | undefined = buffer
        return returnResult
    }
    private getLength_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._StyledString_getLength(this.peer!.ptr)
        return retval
    }
}
export class TextShadowStyleInternal {
    public static fromPtr(ptr: KPointer): TextShadowStyle {
        return new TextShadowStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class TextShadowStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly textShadow: Array<ShadowOptions>
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextShadowStyle.getFinalizer())
        this.textShadow = this.getTextShadow()
    }
    constructor(value: ShadowOptions | Array<ShadowOptions>) {
        this(MaterializedBaseTag.NOP, TextShadowStyle.construct(value))
        this.textShadow = this.getTextShadow()
    }
    static construct(value: ShadowOptions | Array<ShadowOptions>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof ShadowOptions) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as ShadowOptions
            ShadowOptions_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof Array) {
            if (value.length == 0) {
                thisSerializer.writeInt8((1).toByte())
                thisSerializer.writeInt32(0)
            } else {
                const valueElem  = value[0]
                if (valueElem instanceof ShadowOptions) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueForIdx1  = value as Array<ShadowOptions>
                    thisSerializer.writeInt32((valueForIdx1.length).toInt())
                    for (let valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++) {
                        const valueForIdx1TmpElement : ShadowOptions = valueForIdx1[valueForIdx1CounterI]
                        ShadowOptions_serializer.write(thisSerializer, valueForIdx1TmpElement)
                    }
                }
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
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<ShadowOptions> = new Array<ShadowOptions>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = ShadowOptions_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<ShadowOptions> = buffer
        return returnResult
    }
}
export class TextStyleInternal {
    public static fromPtr(ptr: KPointer): TextStyle {
        return new TextStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class TextStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly fontColor?: ResourceColor | undefined
    public readonly fontFamily?: string | undefined
    public readonly fontSize?: double | undefined
    public readonly fontWeight?: int32 | undefined
    public readonly fontStyle?: FontStyle | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextStyle.getFinalizer())
        this.fontColor = this.getFontColor()
        this.fontFamily = this.getFontFamily()
        this.fontSize = this.getFontSize()
        this.fontWeight = this.getFontWeight()
        this.fontStyle = this.getFontStyle()
    }
    constructor(value?: TextStyleInterface) {
        this(MaterializedBaseTag.NOP, TextStyle.construct(value))
        this.fontColor = this.getFontColor()
        this.fontFamily = this.getFontFamily()
        this.fontSize = this.getFontSize()
        this.fontWeight = this.getFontWeight()
        this.fontStyle = this.getFontStyle()
    }
    static construct(value?: TextStyleInterface): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextStyleInterface_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
    private getFontSize(): double | undefined {
        return this.getFontSize_serialize()
    }
    private getFontWeight(): int32 | undefined {
        return this.getFontWeight_serialize()
    }
    private getFontStyle(): FontStyle | undefined {
        return this.getFontStyle_serialize()
    }
    private getFontColor_serialize(): ResourceColor | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontColor(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : ResourceColor | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptUnionSelector : int32 = retvalDeserializer.readInt8()
            let bufferOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (bufferOptUnionSelector == (0).toByte()) {
                bufferOpt = arkui_component_enums_Color.values()[retvalDeserializer.readInt32()]
            } else if (bufferOptUnionSelector == (1).toByte()) {
                bufferOpt = retvalDeserializer.readInt32()
            } else if (bufferOptUnionSelector == (2).toByte()) {
                bufferOpt = (retvalDeserializer.readString() as string)
            } else if (bufferOptUnionSelector == (3).toByte()) {
                bufferOpt = global_resource_Resource_serializer.read(retvalDeserializer)
            } else {
                throw new Error('One of the branches for bufferOpt has to be chosen through deserialisation.')
            }
            buffer = (bufferOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const returnResult : ResourceColor | undefined = buffer
        return returnResult
    }
    private getFontFamily_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontFamily(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : string | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readString() as string)
        }
        const returnResult : string | undefined = buffer
        return returnResult
    }
    private getFontSize_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontSize(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private getFontWeight_serialize(): int32 | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontWeight(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private getFontStyle_serialize(): FontStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._TextStyle_getFontStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : FontStyle | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = FontStyle.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : FontStyle | undefined = buffer
        return returnResult
    }
}
export class UrlStyleInternal {
    public static fromPtr(ptr: KPointer): UrlStyle {
        return new UrlStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class UrlStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public readonly url: string
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, UrlStyle.getFinalizer())
        this.url = this.getUrl()
    }
    constructor(url: string) {
        this(MaterializedBaseTag.NOP, UrlStyle.construct(url))
        this.url = this.getUrl()
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
}
export type StyledStringMarshallingValue = UserDataSpan;
export type StyledStringMarshallCallback = (marshallableVal: StyledStringMarshallingValue) => ArrayBuffer;
export type StyledStringUnmarshallCallback = (buf: ArrayBuffer) => StyledStringMarshallingValue;
export interface StyleOptions {
    start?: int32;
    length?: int32;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
export interface SpanStyle {
    start: int32;
    length: int32;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
export interface TextStyleInterface {
    fontColor?: ResourceColor;
    fontFamily?: arkui_component_units_ResourceStr;
    fontSize?: arkui_component_units_LengthMetrics;
    fontWeight?: int32 | FontWeight | string;
    fontStyle?: FontStyle;
}
export interface DecorationStyleInterface {
    type: TextDecorationType | undefined;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
export interface GestureStyleInterface {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: arkui_component_common_Callback<GestureEvent, void>;
}
export interface ParagraphStyleInterface {
    textAlign?: TextAlign;
    textIndent?: arkui_component_units_LengthMetrics;
    maxLines?: int32;
    overflow?: TextOverflow;
    wordBreak?: WordBreak;
    leadingMargin?: arkui_component_units_LengthMetrics | LeadingMarginPlaceholder;
    paragraphSpacing?: arkui_component_units_LengthMetrics;
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
    resourceValue: arkui_component_units_ResourceStr | undefined;
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
    margin?: arkui_component_units_LengthMetrics | Margin;
    padding?: arkui_component_units_LengthMetrics | Padding;
    borderRadius?: arkui_component_units_LengthMetrics | BorderRadiuses;
}
export interface CustomSpanMetrics {
    width: double;
    height?: double;
}
export interface CustomSpanDrawInfo {
    x: double;
    lineTop: double;
    lineBottom: double;
    baseline: double;
}
export interface CustomSpanMeasureInfo {
    fontSize: double;
}
export class UserDataSpan {
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
export class CustomSpanDrawInfo_serializer {
    public static write(buffer: SerializerBase, value: CustomSpanDrawInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForLineTop  = value.lineTop
        valueSerializer.writeFloat64(valueHolderForLineTop)
        const valueHolderForLineBottom  = value.lineBottom
        valueSerializer.writeFloat64(valueHolderForLineBottom)
        const valueHolderForBaseline  = value.baseline
        valueSerializer.writeFloat64(valueHolderForBaseline)
    }
    public static read(buffer: DeserializerBase): CustomSpanDrawInfo {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : double = valueDeserializer.readFloat64()
        const lineTopTmpResult : double = valueDeserializer.readFloat64()
        const lineBottomTmpResult : double = valueDeserializer.readFloat64()
        const baselineTmpResult : double = valueDeserializer.readFloat64()
        let value : CustomSpanDrawInfo = ({x: xTmpResult, lineTop: lineTopTmpResult, lineBottom: lineBottomTmpResult, baseline: baselineTmpResult} as CustomSpanDrawInfo)
        return value
    }
}
export class CustomSpanMeasureInfo_serializer {
    public static write(buffer: SerializerBase, value: CustomSpanMeasureInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontSize  = value.fontSize
        valueSerializer.writeFloat64(valueHolderForFontSize)
    }
    public static read(buffer: DeserializerBase): CustomSpanMeasureInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fontSizeTmpResult : double = valueDeserializer.readFloat64()
        let value : CustomSpanMeasureInfo = ({fontSize: fontSizeTmpResult} as CustomSpanMeasureInfo)
        return value
    }
}
export class CustomSpanMetrics_serializer {
    public static write(buffer: SerializerBase, value: CustomSpanMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            valueSerializer.writeFloat64(valueHolderForHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomSpanMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : double | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightTmpBuf = valueDeserializer.readFloat64()
        }
        const heightTmpResult : double | undefined = heightTmpBuf
        let value : CustomSpanMetrics = ({width: widthTmpResult, height: heightTmpResult} as CustomSpanMetrics)
        return value
    }
}
export class GestureStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: GestureStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnClick  = value.onClick
        if (valueHolderForOnClick !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnClickTmpValue  = valueHolderForOnClick!
            valueSerializer.holdAndWriteCallback(valueHolderForOnClickTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnLongPress  = value.onLongPress
        if (valueHolderForOnLongPress !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnLongPressTmpValue  = valueHolderForOnLongPress!
            valueSerializer.holdAndWriteCallback(valueHolderForOnLongPressTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GestureStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const onClickTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onClickTmpBuf : ((event: ClickEvent) => void) | undefined = undefined
        if ((onClickTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onClickTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onClickTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onClickTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onClickTmpBufOptClosure  = (event: ClickEvent):void => {
                const onClickTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onClickTmpBufOptBufArgsSerializer.writeInt32(onClickTmpBufOptBufResource.resourceId);
                onClickTmpBufOptBufArgsSerializer.writePointer(onClickTmpBufOptBufCall);
                onClickTmpBufOptBufArgsSerializer.writePointer(onClickTmpBufOptBufCallSync);
                ClickEvent_serializer.write(onClickTmpBufOptBufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, -972351187, onClickTmpBufOptBufArgsSerializer.asBuffer(), onClickTmpBufOptBufArgsSerializer.length());
                onClickTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onClickTmpBufOptClosure, onClickTmpBufOptBufResource)
            onClickTmpBuf = onClickTmpBufOptClosure
        }
        const onClickTmpResult : ((event: ClickEvent) => void) | undefined = onClickTmpBuf
        const onLongPressTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onLongPressTmpBuf : arkui_component_common_Callback<GestureEvent, void> | undefined = undefined
        if ((onLongPressTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onLongPressTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onLongPressTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onLongPressTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onLongPressTmpBufOptClosure  = (data: GestureEvent):void => {
                const onLongPressTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onLongPressTmpBufOptBufArgsSerializer.writeInt32(onLongPressTmpBufOptBufResource.resourceId);
                onLongPressTmpBufOptBufArgsSerializer.writePointer(onLongPressTmpBufOptBufCall);
                onLongPressTmpBufOptBufArgsSerializer.writePointer(onLongPressTmpBufOptBufCallSync);
                GestureEvent_serializer.write(onLongPressTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, 1662060708, onLongPressTmpBufOptBufArgsSerializer.asBuffer(), onLongPressTmpBufOptBufArgsSerializer.length());
                onLongPressTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onLongPressTmpBufOptClosure, onLongPressTmpBufOptBufResource)
            onLongPressTmpBuf = onLongPressTmpBufOptClosure
        }
        const onLongPressTmpResult : arkui_component_common_Callback<GestureEvent, void> | undefined = onLongPressTmpBuf
        let value : GestureStyleInterface = ({onClick: onClickTmpResult, onLongPress: onLongPressTmpResult} as GestureStyleInterface)
        return value
    }
}
export class StyleOptions_serializer {
    public static write(buffer: SerializerBase, value: StyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLength  = value.length
        if (valueHolderForLength !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLengthTmpValue  = valueHolderForLength!
            valueSerializer.writeInt32(valueHolderForLengthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyledKey  = value.styledKey
        valueSerializer.writeInt32(valueHolderForStyledKey.valueOf())
        const valueHolderForStyledValue  = value.styledValue
        if (valueHolderForStyledValue instanceof TextStyle) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForStyledValueForIdx0  = valueHolderForStyledValue as TextStyle
            TextStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx0)
        } else if (valueHolderForStyledValue instanceof DecorationStyle) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForStyledValueForIdx1  = valueHolderForStyledValue as DecorationStyle
            DecorationStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx1)
        } else if (valueHolderForStyledValue instanceof BaselineOffsetStyle) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForStyledValueForIdx2  = valueHolderForStyledValue as BaselineOffsetStyle
            BaselineOffsetStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx2)
        } else if (valueHolderForStyledValue instanceof LetterSpacingStyle) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForStyledValueForIdx3  = valueHolderForStyledValue as LetterSpacingStyle
            LetterSpacingStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx3)
        } else if (valueHolderForStyledValue instanceof TextShadowStyle) {
            valueSerializer.writeInt8((4).toByte())
            const valueHolderForStyledValueForIdx4  = valueHolderForStyledValue as TextShadowStyle
            TextShadowStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx4)
        } else if (valueHolderForStyledValue instanceof GestureStyle) {
            valueSerializer.writeInt8((5).toByte())
            const valueHolderForStyledValueForIdx5  = valueHolderForStyledValue as GestureStyle
            GestureStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx5)
        } else if (valueHolderForStyledValue instanceof ImageAttachment) {
            valueSerializer.writeInt8((6).toByte())
            const valueHolderForStyledValueForIdx6  = valueHolderForStyledValue as ImageAttachment
            ImageAttachment_serializer.write(valueSerializer, valueHolderForStyledValueForIdx6)
        } else if (valueHolderForStyledValue instanceof ParagraphStyle) {
            valueSerializer.writeInt8((7).toByte())
            const valueHolderForStyledValueForIdx7  = valueHolderForStyledValue as ParagraphStyle
            ParagraphStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx7)
        } else if (valueHolderForStyledValue instanceof LineHeightStyle) {
            valueSerializer.writeInt8((8).toByte())
            const valueHolderForStyledValueForIdx8  = valueHolderForStyledValue as LineHeightStyle
            LineHeightStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx8)
        } else if (valueHolderForStyledValue instanceof UrlStyle) {
            valueSerializer.writeInt8((9).toByte())
            const valueHolderForStyledValueForIdx9  = valueHolderForStyledValue as UrlStyle
            UrlStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx9)
        } else if (valueHolderForStyledValue instanceof CustomSpan) {
            valueSerializer.writeInt8((10).toByte())
            const valueHolderForStyledValueForIdx10  = valueHolderForStyledValue as CustomSpan
            CustomSpan_serializer.write(valueSerializer, valueHolderForStyledValueForIdx10)
        } else if (valueHolderForStyledValue instanceof UserDataSpan) {
            valueSerializer.writeInt8((11).toByte())
            const valueHolderForStyledValueForIdx11  = valueHolderForStyledValue as UserDataSpan
            valueSerializer.holdAndWriteObject(valueHolderForStyledValueForIdx11)
        } else if (valueHolderForStyledValue instanceof BackgroundColorStyle) {
            valueSerializer.writeInt8((12).toByte())
            const valueHolderForStyledValueForIdx12  = valueHolderForStyledValue as BackgroundColorStyle
            BackgroundColorStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx12)
        }
    }
    public static read(buffer: DeserializerBase): StyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const lengthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lengthTmpBuf : int32 | undefined = undefined
        if ((lengthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lengthTmpBuf = valueDeserializer.readInt32()
        }
        const lengthTmpResult : int32 | undefined = lengthTmpBuf
        const styledKeyTmpResult : StyledStringKey = StyledStringKey.fromValue(valueDeserializer.readInt32())
        const styledValueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let styledValueTmpBuf : TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle | undefined
        if (styledValueTmpBufUnionSelector == (0).toByte()) {
            styledValueTmpBuf = (TextStyle_serializer.read(valueDeserializer) as TextStyle)
        } else if (styledValueTmpBufUnionSelector == (1).toByte()) {
            styledValueTmpBuf = (DecorationStyle_serializer.read(valueDeserializer) as DecorationStyle)
        } else if (styledValueTmpBufUnionSelector == (2).toByte()) {
            styledValueTmpBuf = (BaselineOffsetStyle_serializer.read(valueDeserializer) as BaselineOffsetStyle)
        } else if (styledValueTmpBufUnionSelector == (3).toByte()) {
            styledValueTmpBuf = (LetterSpacingStyle_serializer.read(valueDeserializer) as LetterSpacingStyle)
        } else if (styledValueTmpBufUnionSelector == (4).toByte()) {
            styledValueTmpBuf = (TextShadowStyle_serializer.read(valueDeserializer) as TextShadowStyle)
        } else if (styledValueTmpBufUnionSelector == (5).toByte()) {
            styledValueTmpBuf = (GestureStyle_serializer.read(valueDeserializer) as GestureStyle)
        } else if (styledValueTmpBufUnionSelector == (6).toByte()) {
            styledValueTmpBuf = (ImageAttachment_serializer.read(valueDeserializer) as ImageAttachment)
        } else if (styledValueTmpBufUnionSelector == (7).toByte()) {
            styledValueTmpBuf = (ParagraphStyle_serializer.read(valueDeserializer) as ParagraphStyle)
        } else if (styledValueTmpBufUnionSelector == (8).toByte()) {
            styledValueTmpBuf = (LineHeightStyle_serializer.read(valueDeserializer) as LineHeightStyle)
        } else if (styledValueTmpBufUnionSelector == (9).toByte()) {
            styledValueTmpBuf = (UrlStyle_serializer.read(valueDeserializer) as UrlStyle)
        } else if (styledValueTmpBufUnionSelector == (10).toByte()) {
            styledValueTmpBuf = (CustomSpan_serializer.read(valueDeserializer) as CustomSpan)
        } else if (styledValueTmpBufUnionSelector == (11).toByte()) {
            styledValueTmpBuf = (valueDeserializer.readObject() as UserDataSpan)
        } else if (styledValueTmpBufUnionSelector == (12).toByte()) {
            styledValueTmpBuf = (BackgroundColorStyle_serializer.read(valueDeserializer) as BackgroundColorStyle)
        } else {
            throw new Error('One of the branches for styledValueTmpBuf has to be chosen through deserialisation.')
        }
        const styledValueTmpResult : StyledStringValue = (styledValueTmpBuf as TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle)
        let value : StyleOptions = ({start: startTmpResult, length: lengthTmpResult, styledKey: styledKeyTmpResult, styledValue: styledValueTmpResult} as StyleOptions)
        return value
    }
}
export class DecorationStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: DecorationStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = (valueHolderForType as TextDecorationType)
            valueSerializer.writeInt32(valueHolderForTypeTmpValue.valueOf())
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
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as TextDecorationStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DecorationStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let typeTmpBuf : TextDecorationType | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = TextDecorationType.fromValue(valueDeserializer.readInt32())
        }
        const typeTmpResult : TextDecorationType | undefined = typeTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
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
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : TextDecorationStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TextDecorationStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : TextDecorationStyle | undefined = styleTmpBuf
        let value : DecorationStyleInterface = ({type: typeTmpResult, color: colorTmpResult, style: styleTmpResult} as DecorationStyleInterface)
        return value
    }
}
export class SpanStyle_serializer {
    public static write(buffer: SerializerBase, value: SpanStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        valueSerializer.writeInt32(valueHolderForStart)
        const valueHolderForLength  = value.length
        valueSerializer.writeInt32(valueHolderForLength)
        const valueHolderForStyledKey  = value.styledKey
        valueSerializer.writeInt32(valueHolderForStyledKey.valueOf())
        const valueHolderForStyledValue  = value.styledValue
        if (valueHolderForStyledValue instanceof TextStyle) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForStyledValueForIdx0  = valueHolderForStyledValue as TextStyle
            TextStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx0)
        } else if (valueHolderForStyledValue instanceof DecorationStyle) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForStyledValueForIdx1  = valueHolderForStyledValue as DecorationStyle
            DecorationStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx1)
        } else if (valueHolderForStyledValue instanceof BaselineOffsetStyle) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForStyledValueForIdx2  = valueHolderForStyledValue as BaselineOffsetStyle
            BaselineOffsetStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx2)
        } else if (valueHolderForStyledValue instanceof LetterSpacingStyle) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForStyledValueForIdx3  = valueHolderForStyledValue as LetterSpacingStyle
            LetterSpacingStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx3)
        } else if (valueHolderForStyledValue instanceof TextShadowStyle) {
            valueSerializer.writeInt8((4).toByte())
            const valueHolderForStyledValueForIdx4  = valueHolderForStyledValue as TextShadowStyle
            TextShadowStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx4)
        } else if (valueHolderForStyledValue instanceof GestureStyle) {
            valueSerializer.writeInt8((5).toByte())
            const valueHolderForStyledValueForIdx5  = valueHolderForStyledValue as GestureStyle
            GestureStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx5)
        } else if (valueHolderForStyledValue instanceof ImageAttachment) {
            valueSerializer.writeInt8((6).toByte())
            const valueHolderForStyledValueForIdx6  = valueHolderForStyledValue as ImageAttachment
            ImageAttachment_serializer.write(valueSerializer, valueHolderForStyledValueForIdx6)
        } else if (valueHolderForStyledValue instanceof ParagraphStyle) {
            valueSerializer.writeInt8((7).toByte())
            const valueHolderForStyledValueForIdx7  = valueHolderForStyledValue as ParagraphStyle
            ParagraphStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx7)
        } else if (valueHolderForStyledValue instanceof LineHeightStyle) {
            valueSerializer.writeInt8((8).toByte())
            const valueHolderForStyledValueForIdx8  = valueHolderForStyledValue as LineHeightStyle
            LineHeightStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx8)
        } else if (valueHolderForStyledValue instanceof UrlStyle) {
            valueSerializer.writeInt8((9).toByte())
            const valueHolderForStyledValueForIdx9  = valueHolderForStyledValue as UrlStyle
            UrlStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx9)
        } else if (valueHolderForStyledValue instanceof CustomSpan) {
            valueSerializer.writeInt8((10).toByte())
            const valueHolderForStyledValueForIdx10  = valueHolderForStyledValue as CustomSpan
            CustomSpan_serializer.write(valueSerializer, valueHolderForStyledValueForIdx10)
        } else if (valueHolderForStyledValue instanceof UserDataSpan) {
            valueSerializer.writeInt8((11).toByte())
            const valueHolderForStyledValueForIdx11  = valueHolderForStyledValue as UserDataSpan
            valueSerializer.holdAndWriteObject(valueHolderForStyledValueForIdx11)
        } else if (valueHolderForStyledValue instanceof BackgroundColorStyle) {
            valueSerializer.writeInt8((12).toByte())
            const valueHolderForStyledValueForIdx12  = valueHolderForStyledValue as BackgroundColorStyle
            BackgroundColorStyle_serializer.write(valueSerializer, valueHolderForStyledValueForIdx12)
        }
    }
    public static read(buffer: DeserializerBase): SpanStyle {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpResult : int32 = valueDeserializer.readInt32()
        const lengthTmpResult : int32 = valueDeserializer.readInt32()
        const styledKeyTmpResult : StyledStringKey = StyledStringKey.fromValue(valueDeserializer.readInt32())
        const styledValueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let styledValueTmpBuf : TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle | undefined
        if (styledValueTmpBufUnionSelector == (0).toByte()) {
            styledValueTmpBuf = (TextStyle_serializer.read(valueDeserializer) as TextStyle)
        } else if (styledValueTmpBufUnionSelector == (1).toByte()) {
            styledValueTmpBuf = (DecorationStyle_serializer.read(valueDeserializer) as DecorationStyle)
        } else if (styledValueTmpBufUnionSelector == (2).toByte()) {
            styledValueTmpBuf = (BaselineOffsetStyle_serializer.read(valueDeserializer) as BaselineOffsetStyle)
        } else if (styledValueTmpBufUnionSelector == (3).toByte()) {
            styledValueTmpBuf = (LetterSpacingStyle_serializer.read(valueDeserializer) as LetterSpacingStyle)
        } else if (styledValueTmpBufUnionSelector == (4).toByte()) {
            styledValueTmpBuf = (TextShadowStyle_serializer.read(valueDeserializer) as TextShadowStyle)
        } else if (styledValueTmpBufUnionSelector == (5).toByte()) {
            styledValueTmpBuf = (GestureStyle_serializer.read(valueDeserializer) as GestureStyle)
        } else if (styledValueTmpBufUnionSelector == (6).toByte()) {
            styledValueTmpBuf = (ImageAttachment_serializer.read(valueDeserializer) as ImageAttachment)
        } else if (styledValueTmpBufUnionSelector == (7).toByte()) {
            styledValueTmpBuf = (ParagraphStyle_serializer.read(valueDeserializer) as ParagraphStyle)
        } else if (styledValueTmpBufUnionSelector == (8).toByte()) {
            styledValueTmpBuf = (LineHeightStyle_serializer.read(valueDeserializer) as LineHeightStyle)
        } else if (styledValueTmpBufUnionSelector == (9).toByte()) {
            styledValueTmpBuf = (UrlStyle_serializer.read(valueDeserializer) as UrlStyle)
        } else if (styledValueTmpBufUnionSelector == (10).toByte()) {
            styledValueTmpBuf = (CustomSpan_serializer.read(valueDeserializer) as CustomSpan)
        } else if (styledValueTmpBufUnionSelector == (11).toByte()) {
            styledValueTmpBuf = (valueDeserializer.readObject() as UserDataSpan)
        } else if (styledValueTmpBufUnionSelector == (12).toByte()) {
            styledValueTmpBuf = (BackgroundColorStyle_serializer.read(valueDeserializer) as BackgroundColorStyle)
        } else {
            throw new Error('One of the branches for styledValueTmpBuf has to be chosen through deserialisation.')
        }
        const styledValueTmpResult : StyledStringValue = (styledValueTmpBuf as TextStyle | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle)
        let value : SpanStyle = ({start: startTmpResult, length: lengthTmpResult, styledKey: styledKeyTmpResult, styledValue: styledValueTmpResult} as SpanStyle)
        return value
    }
}
export class TextStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: TextStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForFontColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForFontColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFamily  = value.fontFamily
        if (valueHolderForFontFamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamilyTmpValue  = valueHolderForFontFamily!
            if (valueHolderForFontFamilyTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontFamilyTmpValueForIdx0  = valueHolderForFontFamilyTmpValue as string
                valueSerializer.writeString(valueHolderForFontFamilyTmpValueForIdx0)
            } else if (valueHolderForFontFamilyTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontFamilyTmpValueForIdx1  = valueHolderForFontFamilyTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontFamilyTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForFontSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx1.valueOf())
            } else if (valueHolderForFontWeightTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as string
                valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontStyle  = value.fontStyle
        if (valueHolderForFontStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontStyleTmpValue  = (valueHolderForFontStyle as FontStyle)
            valueSerializer.writeInt32(valueHolderForFontStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (fontColorTmpBufOptUnionSelector == (0).toByte()) {
                fontColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBufOptUnionSelector == (1).toByte()) {
                fontColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontColorTmpBufOptUnionSelector == (2).toByte()) {
                fontColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBufOptUnionSelector == (3).toByte()) {
                fontColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontColorTmpBufOpt has to be chosen through deserialisation.')
            }
            fontColorTmpBuf = (fontColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const fontFamilyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFamilyTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((fontFamilyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamilyTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontFamilyTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (fontFamilyTmpBufOptUnionSelector == (0).toByte()) {
                fontFamilyTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontFamilyTmpBufOptUnionSelector == (1).toByte()) {
                fontFamilyTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontFamilyTmpBufOpt has to be chosen through deserialisation.')
            }
            fontFamilyTmpBuf = (fontFamilyTmpBufOpt as string | arkui_component_units_Resource)
        }
        const fontFamilyTmpResult : arkui_component_units_ResourceStr | undefined = fontFamilyTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : arkui_component_units_LengthMetrics | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontSizeTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const fontSizeTmpResult : arkui_component_units_LengthMetrics | undefined = fontSizeTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontWeightTmpBuf : int32 | FontWeight | string | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBufOpt : int32 | FontWeight | string | undefined
            if (fontWeightTmpBufOptUnionSelector == (0).toByte()) {
                fontWeightTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontWeightTmpBufOptUnionSelector == (1).toByte()) {
                fontWeightTmpBufOpt = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (fontWeightTmpBufOptUnionSelector == (2).toByte()) {
                fontWeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for fontWeightTmpBufOpt has to be chosen through deserialisation.')
            }
            fontWeightTmpBuf = (fontWeightTmpBufOpt as int32 | FontWeight | string)
        }
        const fontWeightTmpResult : int32 | FontWeight | string | undefined = fontWeightTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontStyleTmpBuf : FontStyle | undefined = undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontStyleTmpBuf = FontStyle.fromValue(valueDeserializer.readInt32())
        }
        const fontStyleTmpResult : FontStyle | undefined = fontStyleTmpBuf
        let value : TextStyleInterface = ({fontColor: fontColorTmpResult, fontFamily: fontFamilyTmpResult, fontSize: fontSizeTmpResult, fontWeight: fontWeightTmpResult, fontStyle: fontStyleTmpResult} as TextStyleInterface)
        return value
    }
}
export class ImageAttachmentLayoutStyle_serializer {
    public static write(buffer: SerializerBase, value: ImageAttachmentLayoutStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            if (valueHolderForMarginTmpValue instanceof arkui_component_units_LengthMetrics) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as arkui_component_units_LengthMetrics
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx0)
            } else if (valueHolderForMarginTmpValue instanceof Margin) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as Margin
                Padding_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPadding  = value.padding
        if (valueHolderForPadding !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPaddingTmpValue  = valueHolderForPadding!
            if (valueHolderForPaddingTmpValue instanceof arkui_component_units_LengthMetrics) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPaddingTmpValueForIdx0  = valueHolderForPaddingTmpValue as arkui_component_units_LengthMetrics
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForPaddingTmpValueForIdx0)
            } else if (valueHolderForPaddingTmpValue instanceof Padding) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPaddingTmpValueForIdx1  = valueHolderForPaddingTmpValue as Padding
                Padding_serializer.write(valueSerializer, valueHolderForPaddingTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof arkui_component_units_LengthMetrics) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as arkui_component_units_LengthMetrics
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageAttachmentLayoutStyle {
        let valueDeserializer : DeserializerBase = buffer
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let marginTmpBuf : arkui_component_units_LengthMetrics | Margin | undefined = undefined
        if ((marginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let marginTmpBufOpt : arkui_component_units_LengthMetrics | Margin | undefined
            if (marginTmpBufOptUnionSelector == (0).toByte()) {
                marginTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (marginTmpBufOptUnionSelector == (1).toByte()) {
                marginTmpBufOpt = Padding_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for marginTmpBufOpt has to be chosen through deserialisation.')
            }
            marginTmpBuf = (marginTmpBufOpt as arkui_component_units_LengthMetrics | Margin)
        }
        const marginTmpResult : arkui_component_units_LengthMetrics | Margin | undefined = marginTmpBuf
        const paddingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let paddingTmpBuf : arkui_component_units_LengthMetrics | Padding | undefined = undefined
        if ((paddingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const paddingTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let paddingTmpBufOpt : arkui_component_units_LengthMetrics | Padding | undefined
            if (paddingTmpBufOptUnionSelector == (0).toByte()) {
                paddingTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (paddingTmpBufOptUnionSelector == (1).toByte()) {
                paddingTmpBufOpt = Padding_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for paddingTmpBufOpt has to be chosen through deserialisation.')
            }
            paddingTmpBuf = (paddingTmpBufOpt as arkui_component_units_LengthMetrics | Padding)
        }
        const paddingTmpResult : arkui_component_units_LengthMetrics | Padding | undefined = paddingTmpBuf
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderRadiusTmpBuf : arkui_component_units_LengthMetrics | BorderRadiuses | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBufOpt : arkui_component_units_LengthMetrics | BorderRadiuses | undefined
            if (borderRadiusTmpBufOptUnionSelector == (0).toByte()) {
                borderRadiusTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (borderRadiusTmpBufOptUnionSelector == (1).toByte()) {
                borderRadiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            borderRadiusTmpBuf = (borderRadiusTmpBufOpt as arkui_component_units_LengthMetrics | BorderRadiuses)
        }
        const borderRadiusTmpResult : arkui_component_units_LengthMetrics | BorderRadiuses | undefined = borderRadiusTmpBuf
        let value : ImageAttachmentLayoutStyle = ({margin: marginTmpResult, padding: paddingTmpResult, borderRadius: borderRadiusTmpResult} as ImageAttachmentLayoutStyle)
        return value
    }
}
export class ParagraphStyleInterface_serializer {
    public static write(buffer: SerializerBase, value: ParagraphStyleInterface): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextAlign  = value.textAlign
        if (valueHolderForTextAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextAlignTmpValue  = (valueHolderForTextAlign as TextAlign)
            valueSerializer.writeInt32(valueHolderForTextAlignTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextIndent  = value.textIndent
        if (valueHolderForTextIndent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextIndentTmpValue  = valueHolderForTextIndent!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTextIndentTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeInt32(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = (valueHolderForOverflow as TextOverflow)
            valueSerializer.writeInt32(valueHolderForOverflowTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWordBreak  = value.wordBreak
        if (valueHolderForWordBreak !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordBreakTmpValue  = (valueHolderForWordBreak as WordBreak)
            valueSerializer.writeInt32(valueHolderForWordBreakTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeadingMargin  = value.leadingMargin
        if (valueHolderForLeadingMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeadingMarginTmpValue  = valueHolderForLeadingMargin!
            if (valueHolderForLeadingMarginTmpValue instanceof arkui_component_units_LengthMetrics) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeadingMarginTmpValueForIdx0  = valueHolderForLeadingMarginTmpValue as arkui_component_units_LengthMetrics
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForLeadingMarginTmpValueForIdx0)
            } else if (valueHolderForLeadingMarginTmpValue instanceof LeadingMarginPlaceholder) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeadingMarginTmpValueForIdx1  = valueHolderForLeadingMarginTmpValue as LeadingMarginPlaceholder
                LeadingMarginPlaceholder_serializer.write(valueSerializer, valueHolderForLeadingMarginTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParagraphSpacing  = value.paragraphSpacing
        if (valueHolderForParagraphSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParagraphSpacingTmpValue  = valueHolderForParagraphSpacing!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForParagraphSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParagraphStyleInterface {
        let valueDeserializer : DeserializerBase = buffer
        const textAlignTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textAlignTmpBuf : TextAlign | undefined = undefined
        if ((textAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textAlignTmpBuf = TextAlign.fromValue(valueDeserializer.readInt32())
        }
        const textAlignTmpResult : TextAlign | undefined = textAlignTmpBuf
        const textIndentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textIndentTmpBuf : arkui_component_units_LengthMetrics | undefined = undefined
        if ((textIndentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textIndentTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const textIndentTmpResult : arkui_component_units_LengthMetrics | undefined = textIndentTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxLinesTmpBuf : int32 | undefined = undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = valueDeserializer.readInt32()
        }
        const maxLinesTmpResult : int32 | undefined = maxLinesTmpBuf
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let overflowTmpBuf : TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TextOverflow.fromValue(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let wordBreakTmpBuf : WordBreak | undefined = undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = WordBreak.fromValue(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : WordBreak | undefined = wordBreakTmpBuf
        const leadingMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leadingMarginTmpBuf : arkui_component_units_LengthMetrics | LeadingMarginPlaceholder | undefined = undefined
        if ((leadingMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leadingMarginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leadingMarginTmpBufOpt : arkui_component_units_LengthMetrics | LeadingMarginPlaceholder | undefined
            if (leadingMarginTmpBufOptUnionSelector == (0).toByte()) {
                leadingMarginTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (leadingMarginTmpBufOptUnionSelector == (1).toByte()) {
                leadingMarginTmpBufOpt = LeadingMarginPlaceholder_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leadingMarginTmpBufOpt has to be chosen through deserialisation.')
            }
            leadingMarginTmpBuf = (leadingMarginTmpBufOpt as arkui_component_units_LengthMetrics | LeadingMarginPlaceholder)
        }
        const leadingMarginTmpResult : arkui_component_units_LengthMetrics | LeadingMarginPlaceholder | undefined = leadingMarginTmpBuf
        const paragraphSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let paragraphSpacingTmpBuf : arkui_component_units_LengthMetrics | undefined = undefined
        if ((paragraphSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paragraphSpacingTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const paragraphSpacingTmpResult : arkui_component_units_LengthMetrics | undefined = paragraphSpacingTmpBuf
        let value : ParagraphStyleInterface = ({textAlign: textAlignTmpResult, textIndent: textIndentTmpResult, maxLines: maxLinesTmpResult, overflow: overflowTmpResult, wordBreak: wordBreakTmpResult, leadingMargin: leadingMarginTmpResult, paragraphSpacing: paragraphSpacingTmpResult} as ParagraphStyleInterface)
        return value
    }
}
export class ImageAttachmentInterface_serializer {
    public static write(buffer: SerializerBase, value: ImageAttachmentInterface): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        image_PixelMap_serializer.write(valueSerializer, valueHolderForValue)
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            SizeOptions_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVerticalAlign  = value.verticalAlign
        if (valueHolderForVerticalAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVerticalAlignTmpValue  = (valueHolderForVerticalAlign as ImageSpanAlignment)
            valueSerializer.writeInt32(valueHolderForVerticalAlignTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForObjectFit  = value.objectFit
        if (valueHolderForObjectFit !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForObjectFitTmpValue  = (valueHolderForObjectFit as ImageFit)
            valueSerializer.writeInt32(valueHolderForObjectFitTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLayoutStyle  = value.layoutStyle
        if (valueHolderForLayoutStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLayoutStyleTmpValue  = valueHolderForLayoutStyle!
            ImageAttachmentLayoutStyle_serializer.write(valueSerializer, valueHolderForLayoutStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColorFilter  = value.colorFilter
        if (valueHolderForColorFilter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorFilterTmpValue  = valueHolderForColorFilter!
            if (valueHolderForColorFilterTmpValue instanceof ColorFilter) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorFilterTmpValueForIdx0  = valueHolderForColorFilterTmpValue as ColorFilter
                ColorFilter_serializer.write(valueSerializer, valueHolderForColorFilterTmpValueForIdx0)
            } else if (valueHolderForColorFilterTmpValue instanceof DrawingColorFilter) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorFilterTmpValueForIdx1  = valueHolderForColorFilterTmpValue as DrawingColorFilter
                drawing_ColorFilter_serializer.write(valueSerializer, valueHolderForColorFilterTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageAttachmentInterface {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpResult : PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf : SizeOptions | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeOptions_serializer.read(valueDeserializer)
        }
        const sizeTmpResult : SizeOptions | undefined = sizeTmpBuf
        const verticalAlignTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let verticalAlignTmpBuf : ImageSpanAlignment | undefined = undefined
        if ((verticalAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            verticalAlignTmpBuf = ImageSpanAlignment.fromValue(valueDeserializer.readInt32())
        }
        const verticalAlignTmpResult : ImageSpanAlignment | undefined = verticalAlignTmpBuf
        const objectFitTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let objectFitTmpBuf : ImageFit | undefined = undefined
        if ((objectFitTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            objectFitTmpBuf = ImageFit.fromValue(valueDeserializer.readInt32())
        }
        const objectFitTmpResult : ImageFit | undefined = objectFitTmpBuf
        const layoutStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let layoutStyleTmpBuf : ImageAttachmentLayoutStyle | undefined = undefined
        if ((layoutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            layoutStyleTmpBuf = ImageAttachmentLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyleTmpResult : ImageAttachmentLayoutStyle | undefined = layoutStyleTmpBuf
        const colorFilterTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorFilterTmpBuf : ColorFilterType | undefined = undefined
        if ((colorFilterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorFilterTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorFilterTmpBufOpt : ColorFilter | DrawingColorFilter | undefined
            if (colorFilterTmpBufOptUnionSelector == (0).toByte()) {
                colorFilterTmpBufOpt = (ColorFilter_serializer.read(valueDeserializer) as ColorFilter)
            } else if (colorFilterTmpBufOptUnionSelector == (1).toByte()) {
                colorFilterTmpBufOpt = (drawing_ColorFilter_serializer.read(valueDeserializer) as drawing.ColorFilter)
            } else {
                throw new Error('One of the branches for colorFilterTmpBufOpt has to be chosen through deserialisation.')
            }
            colorFilterTmpBuf = (colorFilterTmpBufOpt as ColorFilter | DrawingColorFilter)
        }
        const colorFilterTmpResult : ColorFilterType | undefined = colorFilterTmpBuf
        let value : ImageAttachmentInterface = ({value: valueTmpResult, size: sizeTmpResult, verticalAlign: verticalAlignTmpResult, objectFit: objectFitTmpResult, layoutStyle: layoutStyleTmpResult, colorFilter: colorFilterTmpResult} as ImageAttachmentInterface)
        return value
    }
}
export class ResourceImageAttachmentOptions_serializer {
    public static write(buffer: SerializerBase, value: ResourceImageAttachmentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForResourceValue  = value.resourceValue
        if (valueHolderForResourceValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForResourceValueTmpValue  = valueHolderForResourceValue!
            if (valueHolderForResourceValueTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForResourceValueTmpValueForIdx0  = valueHolderForResourceValueTmpValue as string
                valueSerializer.writeString(valueHolderForResourceValueTmpValueForIdx0)
            } else if (valueHolderForResourceValueTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForResourceValueTmpValueForIdx1  = valueHolderForResourceValueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForResourceValueTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            SizeOptions_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVerticalAlign  = value.verticalAlign
        if (valueHolderForVerticalAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVerticalAlignTmpValue  = (valueHolderForVerticalAlign as ImageSpanAlignment)
            valueSerializer.writeInt32(valueHolderForVerticalAlignTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForObjectFit  = value.objectFit
        if (valueHolderForObjectFit !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForObjectFitTmpValue  = (valueHolderForObjectFit as ImageFit)
            valueSerializer.writeInt32(valueHolderForObjectFitTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLayoutStyle  = value.layoutStyle
        if (valueHolderForLayoutStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLayoutStyleTmpValue  = valueHolderForLayoutStyle!
            ImageAttachmentLayoutStyle_serializer.write(valueSerializer, valueHolderForLayoutStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColorFilter  = value.colorFilter
        if (valueHolderForColorFilter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorFilterTmpValue  = valueHolderForColorFilter!
            if (valueHolderForColorFilterTmpValue instanceof ColorFilter) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorFilterTmpValueForIdx0  = valueHolderForColorFilterTmpValue as ColorFilter
                ColorFilter_serializer.write(valueSerializer, valueHolderForColorFilterTmpValueForIdx0)
            } else if (valueHolderForColorFilterTmpValue instanceof DrawingColorFilter) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorFilterTmpValueForIdx1  = valueHolderForColorFilterTmpValue as DrawingColorFilter
                drawing_ColorFilter_serializer.write(valueSerializer, valueHolderForColorFilterTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSyncLoad  = value.syncLoad
        if (valueHolderForSyncLoad !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSyncLoadTmpValue  = valueHolderForSyncLoad!
            valueSerializer.writeBoolean(valueHolderForSyncLoadTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ResourceImageAttachmentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const resourceValueTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let resourceValueTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((resourceValueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const resourceValueTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let resourceValueTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (resourceValueTmpBufOptUnionSelector == (0).toByte()) {
                resourceValueTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (resourceValueTmpBufOptUnionSelector == (1).toByte()) {
                resourceValueTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for resourceValueTmpBufOpt has to be chosen through deserialisation.')
            }
            resourceValueTmpBuf = (resourceValueTmpBufOpt as string | arkui_component_units_Resource)
        }
        const resourceValueTmpResult : arkui_component_units_ResourceStr | undefined = resourceValueTmpBuf
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf : SizeOptions | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeOptions_serializer.read(valueDeserializer)
        }
        const sizeTmpResult : SizeOptions | undefined = sizeTmpBuf
        const verticalAlignTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let verticalAlignTmpBuf : ImageSpanAlignment | undefined = undefined
        if ((verticalAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            verticalAlignTmpBuf = ImageSpanAlignment.fromValue(valueDeserializer.readInt32())
        }
        const verticalAlignTmpResult : ImageSpanAlignment | undefined = verticalAlignTmpBuf
        const objectFitTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let objectFitTmpBuf : ImageFit | undefined = undefined
        if ((objectFitTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            objectFitTmpBuf = ImageFit.fromValue(valueDeserializer.readInt32())
        }
        const objectFitTmpResult : ImageFit | undefined = objectFitTmpBuf
        const layoutStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let layoutStyleTmpBuf : ImageAttachmentLayoutStyle | undefined = undefined
        if ((layoutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            layoutStyleTmpBuf = ImageAttachmentLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyleTmpResult : ImageAttachmentLayoutStyle | undefined = layoutStyleTmpBuf
        const colorFilterTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorFilterTmpBuf : ColorFilterType | undefined = undefined
        if ((colorFilterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorFilterTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorFilterTmpBufOpt : ColorFilter | DrawingColorFilter | undefined
            if (colorFilterTmpBufOptUnionSelector == (0).toByte()) {
                colorFilterTmpBufOpt = (ColorFilter_serializer.read(valueDeserializer) as ColorFilter)
            } else if (colorFilterTmpBufOptUnionSelector == (1).toByte()) {
                colorFilterTmpBufOpt = (drawing_ColorFilter_serializer.read(valueDeserializer) as drawing.ColorFilter)
            } else {
                throw new Error('One of the branches for colorFilterTmpBufOpt has to be chosen through deserialisation.')
            }
            colorFilterTmpBuf = (colorFilterTmpBufOpt as ColorFilter | DrawingColorFilter)
        }
        const colorFilterTmpResult : ColorFilterType | undefined = colorFilterTmpBuf
        const syncLoadTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let syncLoadTmpBuf : boolean | undefined = undefined
        if ((syncLoadTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            syncLoadTmpBuf = valueDeserializer.readBoolean()
        }
        const syncLoadTmpResult : boolean | undefined = syncLoadTmpBuf
        let value : ResourceImageAttachmentOptions = ({resourceValue: resourceValueTmpResult, size: sizeTmpResult, verticalAlign: verticalAlignTmpResult, objectFit: objectFitTmpResult, layoutStyle: layoutStyleTmpResult, colorFilter: colorFilterTmpResult, syncLoad: syncLoadTmpResult} as ResourceImageAttachmentOptions)
        return value
    }
}
export class MutableStyledStringInternal {
    public static fromPtr(ptr: KPointer): MutableStyledString {
        return new MutableStyledString(MaterializedBaseTag.NOP, ptr)
    }
}
export class MutableStyledString extends StyledString implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>) {
        this(MaterializedBaseTag.NOP, MutableStyledString.construct(value, styles))
    }
    static construct(value: string | ImageAttachment | CustomSpan, styles?: Array<StyleOptions>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as string
            thisSerializer.writeString(valueForIdx0)
        } else if (value instanceof ImageAttachment) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as ImageAttachment
            ImageAttachment_serializer.write(thisSerializer, valueForIdx1)
        } else if (value instanceof CustomSpan) {
            thisSerializer.writeInt8((2).toByte())
            const valueForIdx2  = value as CustomSpan
            CustomSpan_serializer.write(thisSerializer, valueForIdx2)
        }
        if (styles !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const stylesTmpValue  = styles!
            thisSerializer.writeInt32((stylesTmpValue.length).toInt())
            for (let stylesTmpValueCounterI = 0; stylesTmpValueCounterI < stylesTmpValue.length; stylesTmpValueCounterI++) {
                const stylesTmpValueTmpElement : StyleOptions = stylesTmpValue[stylesTmpValueCounterI]
                StyleOptions_serializer.write(thisSerializer, stylesTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._MutableStyledString_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._MutableStyledString_getFinalizer()
    }
    public replaceString(start: int32, length: int32, other: string): void {
        const start_casted = start as (int32)
        const length_casted = length as (int32)
        const other_casted = other as (string)
        this.replaceString_serialize(start_casted, length_casted, other_casted)
        return
    }
    public insertString(start: int32, other: string): void {
        const start_casted = start as (int32)
        const other_casted = other as (string)
        this.insertString_serialize(start_casted, other_casted)
        return
    }
    public removeString(start: int32, length: int32): void {
        const start_casted = start as (int32)
        const length_casted = length as (int32)
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
    public removeStyle(start: int32, length: int32, styledKey: StyledStringKey): void {
        const start_casted = start as (int32)
        const length_casted = length as (int32)
        const styledKey_casted = styledKey as (StyledStringKey)
        this.removeStyle_serialize(start_casted, length_casted, styledKey_casted)
        return
    }
    public removeStyles(start: int32, length: int32): void {
        const start_casted = start as (int32)
        const length_casted = length as (int32)
        this.removeStyles_serialize(start_casted, length_casted)
        return
    }
    public clearStyles(): void {
        this.clearStyles_serialize()
        return
    }
    public replaceStyledString(start: int32, length: int32, other: StyledString): void {
        const start_casted = start as (int32)
        const length_casted = length as (int32)
        const other_casted = other as (StyledString)
        this.replaceStyledString_serialize(start_casted, length_casted, other_casted)
        return
    }
    public insertStyledString(start: int32, other: StyledString): void {
        const start_casted = start as (int32)
        const other_casted = other as (StyledString)
        this.insertStyledString_serialize(start_casted, other_casted)
        return
    }
    public appendStyledString(other: StyledString): void {
        const other_casted = other as (StyledString)
        this.appendStyledString_serialize(other_casted)
        return
    }
    private replaceString_serialize(start: int32, length: int32, other: string): void {
        ArkUIGeneratedNativeModule._MutableStyledString_replaceString(this.peer!.ptr, start, length, other)
    }
    private insertString_serialize(start: int32, other: string): void {
        ArkUIGeneratedNativeModule._MutableStyledString_insertString(this.peer!.ptr, start, other)
    }
    private removeString_serialize(start: int32, length: int32): void {
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
    private removeStyle_serialize(start: int32, length: int32, styledKey: StyledStringKey): void {
        ArkUIGeneratedNativeModule._MutableStyledString_removeStyle(this.peer!.ptr, start, length, styledKey.valueOf())
    }
    private removeStyles_serialize(start: int32, length: int32): void {
        ArkUIGeneratedNativeModule._MutableStyledString_removeStyles(this.peer!.ptr, start, length)
    }
    private clearStyles_serialize(): void {
        ArkUIGeneratedNativeModule._MutableStyledString_clearStyles(this.peer!.ptr)
    }
    private replaceStyledString_serialize(start: int32, length: int32, other: StyledString): void {
        ArkUIGeneratedNativeModule._MutableStyledString_replaceStyledString(this.peer!.ptr, start, length, toPeerPtr(other))
    }
    private insertStyledString_serialize(start: int32, other: StyledString): void {
        ArkUIGeneratedNativeModule._MutableStyledString_insertStyledString(this.peer!.ptr, start, toPeerPtr(other))
    }
    private appendStyledString_serialize(other: StyledString): void {
        ArkUIGeneratedNativeModule._MutableStyledString_appendStyledString(this.peer!.ptr, toPeerPtr(other))
    }
}

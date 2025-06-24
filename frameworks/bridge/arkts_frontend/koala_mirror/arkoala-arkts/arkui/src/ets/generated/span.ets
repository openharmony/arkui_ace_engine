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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { LengthMetrics_serializer, LengthMetrics } from "./arkui.Graphics"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ShadowOptions_serializer, ShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { Font_serializer, Font, ResourceColor, Length, Dimension, BorderRadiuses, BorderRadiuses_serializer } from "./units"
import { DecorationStyleInterface_serializer, DecorationStyleInterface } from "./styledString"
import { Color, FontStyle, FontWeight, TextCase } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkBaseSpanPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBaseSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._BaseSpan_construct(peerId, flags)
        const _peer  = new ArkBaseSpanPeer(_peerPtr, peerId, "BaseSpan", flags)
        component?.setPeer(_peer)
        return _peer
    }
    textBackgroundStyleAttribute(value: TextBackgroundStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextBackgroundStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._BaseSpan_textBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    baselineOffsetAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            LengthMetrics_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._BaseSpan_baselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkSpanPeer extends ArkBaseSpanPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Span_construct(peerId, flags)
        const _peer  = new ArkSpanPeer(_peerPtr, peerId, "Span", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSpanOptionsAttribute(value: string | Resource): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            Resource_serializer.write(thisSerializer, value_1)
        }
        ArkUIGeneratedNativeModule._SpanInterface_setSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SpanAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    decorationAttribute(value: DecorationStyleInterface | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            DecorationStyleInterface_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textCaseAttribute(value: TextCase | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextCase)
            thisSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SpanAttribute_textCase(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isShadowOptions(value_value, false, false, false, false, false, false)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_ShadowOptions(value_value))) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Array<ShadowOptions>
                thisSerializer.writeInt32(value_value_1.length as int32)
                for (let i = 0; i < value_value_1.length; i++) {
                    const value_value_1_element : ShadowOptions = value_value_1[i]
                    ShadowOptions_serializer.write(thisSerializer, value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_textShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextBackgroundStyle {
    color?: ResourceColor;
    radius?: Dimension | BorderRadiuses;
}
export interface BaseSpan extends CommonMethod {
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this
    baselineOffset(value: LengthMetrics | undefined): this
    attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkBaseSpanStyle extends ArkCommonMethodStyle implements BaseSpan {
    textBackgroundStyle_value?: TextBackgroundStyle | undefined
    baselineOffset_value?: LengthMetrics | undefined
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        return this
    }
    public baselineOffset(value: LengthMetrics | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: BaseSpan): void {
        super.apply(target)
        if (this.textBackgroundStyle_value !== undefined)
            target.textBackgroundStyle(this.textBackgroundStyle_value!)
        if (this.baselineOffset_value !== undefined)
            target.baselineOffset(this.baselineOffset_value!)
    }
}
export interface SpanAttribute extends BaseSpan {
    font(value: Font | undefined): this
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: number | string | Resource | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    fontFamily(value: string | Resource | undefined): this
    decoration(value: DecorationStyleInterface | undefined): this
    letterSpacing(value: number | string | undefined): this
    textCase(value: TextCase | undefined): this
    lineHeight(value: Length | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this
    attributeModifier(value: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSpanStyle extends ArkBaseSpanStyle implements SpanAttribute {
    font_value?: Font | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: number | string | Resource | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: string | Resource | undefined
    decoration_value?: DecorationStyleInterface | undefined
    letterSpacing_value?: number | string | undefined
    textCase_value?: TextCase | undefined
    lineHeight_value?: Length | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    attributeModifier_value?: AttributeModifier<SpanAttribute> | AttributeModifier<CommonMethod> | undefined
    public font(value: Font | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        return this
    }
    public textCase(value: TextCase | undefined): this {
        return this
    }
    public lineHeight(value: Length | undefined): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SpanAttribute): void {
        super.apply(target)
        if (this.font_value !== undefined)
            target.font(this.font_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.fontStyle_value !== undefined)
            target.fontStyle(this.fontStyle_value!)
        if (this.fontWeight_value !== undefined)
            target.fontWeight(this.fontWeight_value!)
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.decoration_value !== undefined)
            target.decoration(this.decoration_value!)
        if (this.letterSpacing_value !== undefined)
            target.letterSpacing(this.letterSpacing_value!)
        if (this.textCase_value !== undefined)
            target.textCase(this.textCase_value!)
        if (this.lineHeight_value !== undefined)
            target.lineHeight(this.lineHeight_value!)
        if (this.textShadow_value !== undefined)
            target.textShadow(this.textShadow_value!)
    }
}

export class ArkBaseSpanComponent extends ArkCommonMethodComponent implements BaseSpan {
    getPeer(): ArkBaseSpanPeer {
        return (this.peer as ArkBaseSpanPeer)
    }
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (this.checkPriority("textBackgroundStyle")) {
            const value_casted = value as (TextBackgroundStyle | undefined)
            this.getPeer()?.textBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: LengthMetrics | undefined): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.baselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withBaseSpanStyle(receiver: BaseSpan, modifier: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkBaseSpanStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
export class ArkSpanComponent extends ArkBaseSpanComponent implements SpanAttribute {
    getPeer(): ArkSpanPeer {
        return (this.peer as ArkSpanPeer)
    }
    public setSpanOptions(value: string | Resource): this {
        if (this.checkPriority("setSpanOptions")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.setSpanOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.fontAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface | undefined)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textCase(value: TextCase | undefined): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase | undefined)
            this.getPeer()?.textCaseAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: Length | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.textShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSpanStyle(receiver: SpanAttribute, modifier: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSpanStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("SpanImpl")
export function Span(
    value: string | Resource,
    @memo
    content_?: () => void,
): SpanAttribute {
    throw new Error("Not implemented")
}

@memo
export function SpanImpl(
    @memo
    style: ((attributes: SpanAttribute) => void) | undefined,
    value: string | Resource,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSpanComponent>((): ArkSpanComponent => {
        return new ArkSpanComponent()
    })
    NodeAttach<ArkSpanPeer>((): ArkSpanPeer => ArkSpanPeer.create(receiver), (_: ArkSpanPeer): void => {
        receiver.setSpanOptions(value)
        style?.(receiver)
        withSpanStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class TextBackgroundStyle_serializer {
    public static write(buffer: SerializerBase, value: TextBackgroundStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8(value_color_type)
        if ((RuntimeType.UNDEFINED) != (value_color_type)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8(0)
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8(1)
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8(2)
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8(3)
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8(value_radius_type)
        if ((RuntimeType.UNDEFINED) != (value_radius_type)) {
            const value_radius_value  = value_radius!
            let value_radius_value_type : int32 = RuntimeType.UNDEFINED
            value_radius_value_type = runtimeType(value_radius_value)
            if ((RuntimeType.STRING == value_radius_value_type) || (RuntimeType.NUMBER == value_radius_value_type) || (RuntimeType.OBJECT == value_radius_value_type)) {
                valueSerializer.writeInt8(0)
                const value_radius_value_0  = value_radius_value as Dimension
                let value_radius_value_0_type : int32 = RuntimeType.UNDEFINED
                value_radius_value_0_type = runtimeType(value_radius_value_0)
                if (RuntimeType.STRING == value_radius_value_0_type) {
                    valueSerializer.writeInt8(0)
                    const value_radius_value_0_0  = value_radius_value_0 as string
                    valueSerializer.writeString(value_radius_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_radius_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_radius_value_0_1  = value_radius_value_0 as number
                    valueSerializer.writeNumber(value_radius_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_radius_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_radius_value_0_2  = value_radius_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_radius_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(value_radius_value, false, false, false, false)) {
                valueSerializer.writeInt8(1)
                const value_radius_value_1  = value_radius_value as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, value_radius_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextBackgroundStyle {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let color_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (color_buf_runtimeType))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == 0) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == 1) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == 2) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == 3) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const radius_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let radius_buf : Dimension | BorderRadiuses | undefined
        if ((RuntimeType.UNDEFINED) != (radius_buf_runtimeType))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : Dimension | BorderRadiuses | undefined
            if (radius_buf__selector == 0) {
                const radius_buf__u_selector : int32 = valueDeserializer.readInt8()
                let radius_buf__u : string | number | Resource | undefined
                if (radius_buf__u_selector == 0) {
                    radius_buf__u = (valueDeserializer.readString() as string)
                }
                else if (radius_buf__u_selector == 1) {
                    radius_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (radius_buf__u_selector == 2) {
                    radius_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for radius_buf__u has to be chosen through deserialisation.")
                }
                radius_buf_ = (radius_buf__u as string | number | Resource)
            }
            else if (radius_buf__selector == 1) {
                radius_buf_ = BorderRadiuses_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as Dimension | BorderRadiuses)
        }
        const radius_result : Dimension | BorderRadiuses | undefined = radius_buf
        let value : TextBackgroundStyle = ({color: color_result, radius: radius_result} as TextBackgroundStyle)
        return value
    }
}

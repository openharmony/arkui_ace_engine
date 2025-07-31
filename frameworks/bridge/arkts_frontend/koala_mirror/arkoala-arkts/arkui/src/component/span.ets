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
import { LengthMetrics_serializer, LengthMetrics } from "./../generated/arkui.Graphics"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ShadowOptions_serializer, ShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { Font_serializer, Font, ResourceColor, Length, Dimension, BorderRadiuses, BorderRadiuses_serializer } from "./units"
import { DecorationStyleInterface_serializer, DecorationStyleInterface } from "./styledString"
import { Color, FontStyle, TextCase } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setTextBackgroundStyleAttribute(value: TextBackgroundStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextBackgroundStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._BaseSpan_setTextBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBaselineOffsetAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            LengthMetrics_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._BaseSpan_setBaselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as Resource
            Resource_serializer.write(thisSerializer, value_1)
        }
        ArkUIGeneratedNativeModule._SpanInterface_setSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDecorationAttribute(value: DecorationStyleInterface | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DecorationStyleInterface_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextCaseAttribute(value: TextCase | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextCase)
            thisSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setTextCase(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isShadowOptions(value_value, false, false, false, false, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_ShadowOptions(value_value))) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Array<ShadowOptions>
                thisSerializer.writeInt32((value_value_1.length).toInt())
                for (let value_value_1_counter_i = 0; value_value_1_counter_i < value_value_1.length; value_value_1_counter_i++) {
                    const value_value_1_element : ShadowOptions = value_value_1[value_value_1_counter_i]
                    ShadowOptions_serializer.write(thisSerializer, value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextBackgroundStyle {
    color?: ResourceColor;
    radius?: Dimension | BorderRadiuses;
}
export interface BaseSpan extends CommonMethod {
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        throw new Error("Unimplemented method textBackgroundStyle")
    }
    baselineOffset(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method baselineOffset")
    }
    attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    font(value: Font | undefined): this {
        throw new Error("Unimplemented method font")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    fontFamily(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        throw new Error("Unimplemented method decoration")
    }
    textCase(value: TextCase | undefined): this {
        throw new Error("Unimplemented method textCase")
    }
    lineHeight(value: Length | undefined): this {
        throw new Error("Unimplemented method lineHeight")
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error("Unimplemented method textShadow")
    }
    attributeModifier(value: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSpanStyle extends ArkBaseSpanStyle implements SpanAttribute {
    font_value?: Font | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: number | string | Resource | undefined
    fontStyle_value?: FontStyle | undefined
    fontFamily_value?: string | Resource | undefined
    decoration_value?: DecorationStyleInterface | undefined
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
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
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
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.decoration_value !== undefined)
            target.decoration(this.decoration_value!)
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
            this.getPeer()?.setTextBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: LengthMetrics | undefined): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setBaselineOffsetAttribute(value_casted)
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
        if (modifier!.isUpdater())
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
            this.getPeer()?.setFontAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public textCase(value: TextCase | undefined): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase | undefined)
            this.getPeer()?.setTextCaseAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: Length | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.setTextShadowAttribute(value_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Span")
// export function Span(
//     value: string | Resource,
//     @memo
//     content_?: () => void,
// ): SpanAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Span(
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

export class ArkBaseSpanSet extends ArkCommonMethodSet implements BaseSpan {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _textBackgroundStyle_flag?: boolean
    _textBackgroundStyle0_value?: TextBackgroundStyle | undefined
    _baselineOffset_flag?: boolean
    _baselineOffset0_value?: LengthMetrics | undefined
    applyModifierPatch(component: BaseSpan): void {
        if (this._textBackgroundStyle_flag)
            component.textBackgroundStyle((this._textBackgroundStyle0_value as TextBackgroundStyle | undefined))
        if (this._baselineOffset_flag)
            component.baselineOffset((this._baselineOffset0_value as LengthMetrics | undefined))
    }
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        this._textBackgroundStyle_flag = true
        this._textBackgroundStyle0_value = value
        return this
    }
    public baselineOffset(value: LengthMetrics | undefined): this {
        this._baselineOffset_flag = true
        this._baselineOffset0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ArkSpanSet extends ArkBaseSpanSet implements SpanAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _font_flag?: boolean
    _font0_value?: Font | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: number | string | Resource | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: string | Resource | undefined
    _decoration_flag?: boolean
    _decoration0_value?: DecorationStyleInterface | undefined
    _textCase_flag?: boolean
    _textCase0_value?: TextCase | undefined
    _lineHeight_flag?: boolean
    _lineHeight0_value?: Length | undefined
    _textShadow_flag?: boolean
    _textShadow0_value?: ShadowOptions | Array<ShadowOptions> | undefined
    applyModifierPatch(component: SpanAttribute): void {
        if (this._font_flag)
            component.font((this._font0_value as Font | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as number | string | Resource | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as string | Resource | undefined))
        if (this._decoration_flag)
            component.decoration((this._decoration0_value as DecorationStyleInterface | undefined))
        if (this._textCase_flag)
            component.textCase((this._textCase0_value as TextCase | undefined))
        if (this._lineHeight_flag)
            component.lineHeight((this._lineHeight0_value as Length | undefined))
        if (this._textShadow_flag)
            component.textShadow((this._textShadow0_value as ShadowOptions | Array<ShadowOptions> | undefined))
    }
    public font(value: Font | undefined): this {
        this._font_flag = true
        this._font0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this._fontStyle_flag = true
        this._fontStyle0_value = value
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        this._decoration_flag = true
        this._decoration0_value = value
        return this
    }
    public textCase(value: TextCase | undefined): this {
        this._textCase_flag = true
        this._textCase0_value = value
        return this
    }
    public lineHeight(value: Length | undefined): this {
        this._lineHeight_flag = true
        this._lineHeight0_value = value
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        this._textShadow_flag = true
        this._textShadow0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextBackgroundStyle_serializer {
    public static write(buffer: SerializerBase, value: TextBackgroundStyle): void {
        let valueSerializer : SerializerBase = buffer
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
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8((value_radius_type).toChar())
        if ((value_radius_type) != (RuntimeType.UNDEFINED)) {
            const value_radius_value  = value_radius!
            let value_radius_value_type : int32 = RuntimeType.UNDEFINED
            value_radius_value_type = runtimeType(value_radius_value)
            if ((RuntimeType.STRING == value_radius_value_type) || (RuntimeType.NUMBER == value_radius_value_type) || (RuntimeType.OBJECT == value_radius_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_radius_value_0  = value_radius_value as Dimension
                let value_radius_value_0_type : int32 = RuntimeType.UNDEFINED
                value_radius_value_0_type = runtimeType(value_radius_value_0)
                if (RuntimeType.STRING == value_radius_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_radius_value_0_0  = value_radius_value_0 as string
                    valueSerializer.writeString(value_radius_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_radius_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_radius_value_0_1  = value_radius_value_0 as number
                    valueSerializer.writeNumber(value_radius_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_radius_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_radius_value_0_2  = value_radius_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_radius_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(value_radius_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_radius_value_1  = value_radius_value as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, value_radius_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextBackgroundStyle {
        let valueDeserializer : DeserializerBase = buffer
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
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : Dimension | BorderRadiuses | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : Dimension | BorderRadiuses | undefined
            if (radius_buf__selector == (0).toChar()) {
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
            else if (radius_buf__selector == (1).toChar()) {
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

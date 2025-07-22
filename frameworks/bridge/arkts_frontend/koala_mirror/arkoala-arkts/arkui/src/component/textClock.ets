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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, ShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { intl_DateTimeOptions_serializer, intl } from "./../generated/ohos.intl"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ResourceStr, ResourceColor, Length } from "./units"
import { Color, FontStyle, FontWeight } from "./enums"
import { ContentModifier, AttributeModifier, hookTextClockContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextClockControllerInternal {
    public static fromPtr(ptr: KPointer): TextClockController {
        return new TextClockController(ptr)
    }
}
export class TextClockController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextClockController.getFinalizer())
    }
    constructor() {
        this(TextClockController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextClockController_getFinalizer()
    }
    public start(): void {
        this.start_serialize()
        return
    }
    public stop(): void {
        this.stop_serialize()
        return
    }
    private start_serialize(): void {
        ArkUIGeneratedNativeModule._TextClockController_start(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._TextClockController_stop(this.peer!.ptr)
    }
}
export class ArkTextClockPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextClockPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextClock_construct(peerId, flags)
        const _peer  = new ArkTextClockPeer(_peerPtr, peerId, "TextClock", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextClockOptionsAttribute(options?: TextClockOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            TextClockOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextClockInterface_setTextClockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFormatAttribute(value: ResourceStr | undefined): void {
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
        ArkUIGeneratedNativeModule._TextClockAttribute_setFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDateChangeAttribute(value: ((value: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setOnDateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | string | undefined): void {
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
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: ResourceStr | undefined): void {
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
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextClockAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<TextClockConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDateTimeOptionsAttribute(value: intl.DateTimeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            intl_DateTimeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setDateTimeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextClockConfiguration extends CommonConfiguration<TextClockConfiguration> {
    timeZoneOffset: number;
    started: boolean;
    timeValue: number;
}
export interface TextClockOptions {
    timeZoneOffset?: number;
    controller?: TextClockController;
}
export interface TextClockAttribute extends CommonMethod {
    format(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method format")
    }
    onDateChange(value: ((value: number) => void) | undefined): this {
        throw new Error("Unimplemented method onDateChange")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: Length | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    fontFamily(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error("Unimplemented method textShadow")
    }
    fontFeature(value: string | undefined): this {
        throw new Error("Unimplemented method fontFeature")
    }
    contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        throw new Error("Unimplemented method dateTimeOptions")
    }
    attributeModifier(value: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTextClockStyle extends ArkCommonMethodStyle implements TextClockAttribute {
    format_value?: ResourceStr | undefined
    onDateChange_value?: ((value: number) => void) | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: ResourceStr | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    fontFeature_value?: string | undefined
    contentModifier_value?: ContentModifier<TextClockConfiguration> | undefined
    dateTimeOptions_value?: intl.DateTimeOptions | undefined
    attributeModifier_value?: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined
    public format(value: ResourceStr | undefined): this {
        return this
    }
    public onDateChange(value: ((value: number) => void) | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: Length | undefined): this {
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    public fontFeature(value: string | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        return this
    }
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TextClockAttribute): void {
        super.apply(target)
        if (this.format_value !== undefined)
            target.format(this.format_value!)
        if (this.onDateChange_value !== undefined)
            target.onDateChange(this.onDateChange_value!)
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
        if (this.textShadow_value !== undefined)
            target.textShadow(this.textShadow_value!)
        if (this.fontFeature_value !== undefined)
            target.fontFeature(this.fontFeature_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
        if (this.dateTimeOptions_value !== undefined)
            target.dateTimeOptions(this.dateTimeOptions_value!)
    }
}

export class ArkTextClockComponent extends ArkCommonMethodComponent implements TextClockAttribute {
    getPeer(): ArkTextClockPeer {
        return (this.peer as ArkTextClockPeer)
    }
    public setTextClockOptions(options?: TextClockOptions): this {
        if (this.checkPriority("setTextClockOptions")) {
            const options_casted = options as (TextClockOptions | undefined)
            this.getPeer()?.setTextClockOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public format(value: ResourceStr | undefined): this {
        if (this.checkPriority("format")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.setFormatAttribute(value_casted)
            return this
        }
        return this
    }
    public onDateChange(value: ((value: number) => void) | undefined): this {
        if (this.checkPriority("onDateChange")) {
            const value_casted = value as (((value: number) => void) | undefined)
            this.getPeer()?.setOnDateChangeAttribute(value_casted)
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
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
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
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
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
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<TextClockConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        if (this.checkPriority("dateTimeOptions")) {
            const value_casted = value as (intl.DateTimeOptions | undefined)
            this.getPeer()?.setDateTimeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTextClockStyle(receiver: TextClockAttribute, modifier: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTextClockStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("TextClock")
// export function TextClock(
//     options?: TextClockOptions,
//     @memo
//     content_?: () => void,
// ): TextClockAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function TextClock(
    @memo
    style: ((attributes: TextClockAttribute) => void) | undefined,
    options?: TextClockOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextClockComponent>((): ArkTextClockComponent => {
        return new ArkTextClockComponent()
    })
    NodeAttach<ArkTextClockPeer>((): ArkTextClockPeer => ArkTextClockPeer.create(receiver), (_: ArkTextClockPeer): void => {
        receiver.setTextClockOptions(options)
        style?.(receiver)
        withTextClockStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTextClockSet extends ArkCommonMethodSet implements TextClockAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _format_flag?: boolean
    _format0_value?: ResourceStr | undefined
    _onDateChange_flag?: boolean
    _onDateChange0_value?: ((value: number) => void) | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: Length | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | string | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: ResourceStr | undefined
    _textShadow_flag?: boolean
    _textShadow0_value?: ShadowOptions | Array<ShadowOptions> | undefined
    _fontFeature_flag?: boolean
    _fontFeature0_value?: string | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<TextClockConfiguration> | undefined
    _dateTimeOptions_flag?: boolean
    _dateTimeOptions0_value?: intl.DateTimeOptions | undefined
    applyModifierPatch(component: TextClockAttribute): void {
        if (this._format_flag)
            component.format((this._format0_value as ResourceStr | undefined))
        if (this._onDateChange_flag)
            component.onDateChange((this._onDateChange0_value as ((value: number) => void) | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as Length | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | string | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as ResourceStr | undefined))
        if (this._textShadow_flag)
            component.textShadow((this._textShadow0_value as ShadowOptions | Array<ShadowOptions> | undefined))
        if (this._fontFeature_flag)
            component.fontFeature((this._fontFeature0_value as string | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<TextClockConfiguration> | undefined))
        if (this._dateTimeOptions_flag)
            component.dateTimeOptions((this._dateTimeOptions0_value as intl.DateTimeOptions | undefined))
    }
    public format(value: ResourceStr | undefined): this {
        this._format_flag = true
        this._format0_value = value
        return this
    }
    public onDateChange(value: ((value: number) => void) | undefined): this {
        this._onDateChange_flag = true
        this._onDateChange0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontSize(value: Length | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this._fontStyle_flag = true
        this._fontStyle0_value = value
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        this._textShadow_flag = true
        this._textShadow0_value = value
        return this
    }
    public fontFeature(value: string | undefined): this {
        this._fontFeature_flag = true
        this._fontFeature0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        this._dateTimeOptions_flag = true
        this._dateTimeOptions0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextClockConfiguration_serializer {
    public static write(buffer: SerializerBase, value: TextClockConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_timeZoneOffset  = value.timeZoneOffset
        valueSerializer.writeNumber(value_timeZoneOffset)
        const value_started  = value.started
        valueSerializer.writeBoolean(value_started)
        const value_timeValue  = value.timeValue
        valueSerializer.writeNumber(value_timeValue)
    }
    public static read(buffer: DeserializerBase): TextClockConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<TextClockConfiguration> = (valueDeserializer.readObject() as ContentModifier<TextClockConfiguration>)
        const timeZoneOffset_result : number = (valueDeserializer.readNumber() as number)
        const started_result : boolean = valueDeserializer.readBoolean()
        const timeValue_result : number = (valueDeserializer.readNumber() as number)
        let value : TextClockConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, timeZoneOffset: timeZoneOffset_result, started: started_result, timeValue: timeValue_result} as TextClockConfiguration)
        return value
    }
}
export class TextClockController_serializer {
    public static write(buffer: SerializerBase, value: TextClockController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextClockController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextClockControllerInternal.fromPtr(ptr)
    }
}
export class TextClockOptions_serializer {
    public static write(buffer: SerializerBase, value: TextClockOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_timeZoneOffset  = value.timeZoneOffset
        let value_timeZoneOffset_type : int32 = RuntimeType.UNDEFINED
        value_timeZoneOffset_type = runtimeType(value_timeZoneOffset)
        valueSerializer.writeInt8((value_timeZoneOffset_type).toChar())
        if ((value_timeZoneOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_timeZoneOffset_value  = value_timeZoneOffset!
            valueSerializer.writeNumber(value_timeZoneOffset_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            TextClockController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): TextClockOptions {
        let valueDeserializer : DeserializerBase = buffer
        const timeZoneOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeZoneOffset_buf : number | undefined
        if ((timeZoneOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeZoneOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const timeZoneOffset_result : number | undefined = timeZoneOffset_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : TextClockController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (TextClockController_serializer.read(valueDeserializer) as TextClockController)
        }
        const controller_result : TextClockController | undefined = controller_buf
        let value : TextClockOptions = ({timeZoneOffset: timeZoneOffset_result, controller: controller_result} as TextClockOptions)
        return value
    }
}

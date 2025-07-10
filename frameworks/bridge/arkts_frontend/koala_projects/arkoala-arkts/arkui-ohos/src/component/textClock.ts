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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Callback_Number_Void } from "./alphabetIndexer"
import { ResourceColor, Length, ResourceStr } from "./units"
import { FontStyle, FontWeight, Color } from "./enums"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { DateTimeOptions } from "./arkui-intl"
import { Resource } from "global/resource"
import { NodeAttach, remember } from "@koalaui/runtime"

export class TextClockControllerInternal {
    public static fromPtr(ptr: KPointer): TextClockController {
        const obj : TextClockController = new TextClockController()
        obj.peer = new Finalizable(ptr, TextClockController.getFinalizer())
        return obj
    }
}
export class TextClockController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textclockcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextClockController.ctor_textclockcontroller()
        this.peer = new Finalizable(ctorPtr, TextClockController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextClockController_getFinalizer()
    }
    public start(): void {
        this.start_serialize();
        return;
    }
    public stop(): void {
        this.stop_serialize();
        return;
    }
    private start_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_start(this.peer!.ptr)
        return retval
    }
    private stop_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_stop(this.peer!.ptr)
        return retval
    }
}
export class ArkTextClockPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTextClockPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextClock_construct(peerId, flags)
        const _peer  = new ArkTextClockPeer(_peerPtr, peerId, "TextClock", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextClockOptionsAttribute(options?: TextClockOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextClockOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextClockInterface_setTextClockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    formatAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_format(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDateChangeAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_onDateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isShadowOptions(value_value, false, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ShadowOptions
                thisSerializer.writeShadowOptions(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_ShadowOptions(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Array<ShadowOptions>
                thisSerializer.writeInt32(value_value_1.length as int32)
                for (let i = 0; i < value_value_1.length; i++) {
                    const value_value_1_element : ShadowOptions = value_value_1[i]
                    thisSerializer.writeShadowOptions(value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_textShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_fontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dateTimeOptionsAttribute(value: DateTimeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDateTimeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_dateTimeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextClockConfiguration extends CommonConfiguration {
    timeZoneOffset: number;
    started: boolean;
    timeValue: number;
}
export interface TextClockOptions {
    timeZoneOffset?: number;
    controller?: TextClockController;
}
export type TextClockInterface = (options?: TextClockOptions) => TextClockAttribute;
export interface TextClockAttribute extends CommonMethod {
    format(value: string | undefined): this
    onDateChange(value: ((index: number) => void) | undefined): this
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: Length | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    fontFamily(value: ResourceStr | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this
    fontFeature(value: string | undefined): this
    contentModifier(value: ContentModifier | undefined): this
    dateTimeOptions(value: DateTimeOptions | undefined): this
}
export class ArkTextClockStyle extends ArkCommonMethodStyle implements TextClockAttribute {
    format_value?: string | undefined
    onDateChange_value?: ((index: number) => void) | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: ResourceStr | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    fontFeature_value?: string | undefined
    contentModifier_value?: ContentModifier | undefined
    dateTimeOptions_value?: DateTimeOptions | undefined
    public format(value: string | undefined): this {
        return this
    }
    public onDateChange(value: ((index: number) => void) | undefined): this {
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
    public contentModifier(value: ContentModifier | undefined): this {
        return this
    }
    public dateTimeOptions(value: DateTimeOptions | undefined): this {
        return this
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
    public format(value: string | undefined): this {
        if (this.checkPriority("format")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.formatAttribute(value_casted)
            return this
        }
        return this
    }
    public onDateChange(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onDateChange")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onDateChangeAttribute(value_casted)
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
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
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
    public fontFamily(value: ResourceStr | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.fontFamilyAttribute(value_casted)
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
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public dateTimeOptions(value: DateTimeOptions | undefined): this {
        if (this.checkPriority("dateTimeOptions")) {
            const value_casted = value as (DateTimeOptions | undefined)
            this.getPeer()?.dateTimeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function TextClock(
    /** @memo */
    style: ((attributes: TextClockAttribute) => void) | undefined,
    options?: TextClockOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkTextClockComponent()
    })
    NodeAttach<ArkTextClockPeer>((): ArkTextClockPeer => ArkTextClockPeer.create(receiver), (_: ArkTextClockPeer) => {
        receiver.setTextClockOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

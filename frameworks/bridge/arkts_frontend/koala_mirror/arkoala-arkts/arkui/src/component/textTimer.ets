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
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ResourceColor, Length, ResourceStr } from "./units"
import { Color, FontStyle, FontWeight } from "./enums"
import { ContentModifier, AttributeModifier, hookTextTimerContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextTimerControllerInternal {
    public static fromPtr(ptr: KPointer): TextTimerController {
        return new TextTimerController(ptr)
    }
}
export class TextTimerController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextTimerController.getFinalizer())
    }
    constructor() {
        this(TextTimerController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextTimerController_getFinalizer()
    }
    public start(): void {
        this.start_serialize()
        return
    }
    public pause(): void {
        this.pause_serialize()
        return
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private start_serialize(): void {
        ArkUIGeneratedNativeModule._TextTimerController_start(this.peer!.ptr)
    }
    private pause_serialize(): void {
        ArkUIGeneratedNativeModule._TextTimerController_pause(this.peer!.ptr)
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._TextTimerController_reset(this.peer!.ptr)
    }
}
export class ArkTextTimerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextTimerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextTimer_construct(peerId, flags)
        const _peer  = new ArkTextTimerPeer(_peerPtr, peerId, "TextTimer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextTimerOptionsAttribute(options?: TextTimerOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            TextTimerOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextTimerInterface_setTextTimerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFormatAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | ResourceStr | undefined): void {
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
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as ResourceStr
                let value_value_2_type : int32 = RuntimeType.UNDEFINED
                value_value_2_type = runtimeType(value_value_2)
                if (RuntimeType.STRING == value_value_2_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_2_0  = value_value_2 as string
                    thisSerializer.writeString(value_value_2_0)
                }
                else if (RuntimeType.OBJECT == value_value_2_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_2_1  = value_value_2 as Resource
                    Resource_serializer.write(thisSerializer, value_value_2_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTimerAttribute(value: ((utc: number,elapsedTime: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setOnTimer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<TextTimerConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextTimerConfiguration extends CommonConfiguration<TextTimerConfiguration> {
    count: number;
    isCountDown: boolean;
    started: boolean;
    elapsedTime: number;
}
export interface TextTimerOptions {
    isCountDown?: boolean;
    controller?: TextTimerController;
}
export interface TextTimerAttribute extends CommonMethod {
    format(value: string | undefined): this {
        throw new Error("Unimplemented method format")
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
    fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    fontFamily(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    onTimer(value: ((utc: number,elapsedTime: number) => void) | undefined): this {
        throw new Error("Unimplemented method onTimer")
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error("Unimplemented method textShadow")
    }
    contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTextTimerStyle extends ArkCommonMethodStyle implements TextTimerAttribute {
    format_value?: string | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | ResourceStr | undefined
    fontFamily_value?: ResourceStr | undefined
    onTimer_value?: ((utc: number,elapsedTime: number) => void) | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    contentModifier_value?: ContentModifier<TextTimerConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined
    public format(value: string | undefined): this {
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
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        return this
    }
    public onTimer(value: ((utc: number,elapsedTime: number) => void) | undefined): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TextTimerAttribute): void {
        super.apply(target)
        if (this.format_value !== undefined)
            target.format(this.format_value!)
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
        if (this.onTimer_value !== undefined)
            target.onTimer(this.onTimer_value!)
        if (this.textShadow_value !== undefined)
            target.textShadow(this.textShadow_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}

export class ArkTextTimerComponent extends ArkCommonMethodComponent implements TextTimerAttribute {
    getPeer(): ArkTextTimerPeer {
        return (this.peer as ArkTextTimerPeer)
    }
    public setTextTimerOptions(options?: TextTimerOptions): this {
        if (this.checkPriority("setTextTimerOptions")) {
            const options_casted = options as (TextTimerOptions | undefined)
            this.getPeer()?.setTextTimerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public format(value: string | undefined): this {
        if (this.checkPriority("format")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFormatAttribute(value_casted)
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
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | ResourceStr | undefined)
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
    public onTimer(value: ((utc: number,elapsedTime: number) => void) | undefined): this {
        if (this.checkPriority("onTimer")) {
            const value_casted = value as (((utc: number,elapsedTime: number) => void) | undefined)
            this.getPeer()?.setOnTimerAttribute(value_casted)
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
    public contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<TextTimerConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTextTimerStyle(receiver: TextTimerAttribute, modifier: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTextTimerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("TextTimer")
// export function TextTimer(
//     options?: TextTimerOptions,
//     @memo
//     content_?: () => void,
// ): TextTimerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function TextTimer(
    @memo
    style: ((attributes: TextTimerAttribute) => void) | undefined,
    options?: TextTimerOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextTimerComponent>((): ArkTextTimerComponent => {
        return new ArkTextTimerComponent()
    })
    NodeAttach<ArkTextTimerPeer>((): ArkTextTimerPeer => ArkTextTimerPeer.create(receiver), (_: ArkTextTimerPeer): void => {
        receiver.setTextTimerOptions(options)
        style?.(receiver)
        withTextTimerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTextTimerSet extends ArkCommonMethodSet implements TextTimerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _format_flag?: boolean
    _format0_value?: string | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: Length | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | ResourceStr | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: ResourceStr | undefined
    _onTimer_flag?: boolean
    _onTimer0_value?: ((utc: number,elapsedTime: number) => void) | undefined
    _textShadow_flag?: boolean
    _textShadow0_value?: ShadowOptions | Array<ShadowOptions> | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<TextTimerConfiguration> | undefined
    applyModifierPatch(component: TextTimerAttribute): void {
        if (this._format_flag)
            component.format((this._format0_value as string | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as Length | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | ResourceStr | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as ResourceStr | undefined))
        if (this._onTimer_flag)
            component.onTimer((this._onTimer0_value as ((utc: number,elapsedTime: number) => void) | undefined))
        if (this._textShadow_flag)
            component.textShadow((this._textShadow0_value as ShadowOptions | Array<ShadowOptions> | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<TextTimerConfiguration> | undefined))
    }
    public format(value: string | undefined): this {
        this._format_flag = true
        this._format0_value = value
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
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public onTimer(value: ((utc: number,elapsedTime: number) => void) | undefined): this {
        this._onTimer_flag = true
        this._onTimer0_value = value
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        this._textShadow_flag = true
        this._textShadow0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextTimerConfiguration_serializer {
    public static write(buffer: SerializerBase, value: TextTimerConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_count  = value.count
        valueSerializer.writeNumber(value_count)
        const value_isCountDown  = value.isCountDown
        valueSerializer.writeBoolean(value_isCountDown)
        const value_started  = value.started
        valueSerializer.writeBoolean(value_started)
        const value_elapsedTime  = value.elapsedTime
        valueSerializer.writeNumber(value_elapsedTime)
    }
    public static read(buffer: DeserializerBase): TextTimerConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<TextTimerConfiguration> = (valueDeserializer.readObject() as ContentModifier<TextTimerConfiguration>)
        const count_result : number = (valueDeserializer.readNumber() as number)
        const isCountDown_result : boolean = valueDeserializer.readBoolean()
        const started_result : boolean = valueDeserializer.readBoolean()
        const elapsedTime_result : number = (valueDeserializer.readNumber() as number)
        let value : TextTimerConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, count: count_result, isCountDown: isCountDown_result, started: started_result, elapsedTime: elapsedTime_result} as TextTimerConfiguration)
        return value
    }
}
export class TextTimerController_serializer {
    public static write(buffer: SerializerBase, value: TextTimerController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextTimerController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextTimerControllerInternal.fromPtr(ptr)
    }
}
export class TextTimerOptions_serializer {
    public static write(buffer: SerializerBase, value: TextTimerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_isCountDown  = value.isCountDown
        let value_isCountDown_type : int32 = RuntimeType.UNDEFINED
        value_isCountDown_type = runtimeType(value_isCountDown)
        valueSerializer.writeInt8((value_isCountDown_type).toChar())
        if ((value_isCountDown_type) != (RuntimeType.UNDEFINED)) {
            const value_isCountDown_value  = value_isCountDown!
            valueSerializer.writeBoolean(value_isCountDown_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            TextTimerController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): TextTimerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isCountDown_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isCountDown_buf : boolean | undefined
        if ((isCountDown_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isCountDown_buf = valueDeserializer.readBoolean()
        }
        const isCountDown_result : boolean | undefined = isCountDown_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : TextTimerController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (TextTimerController_serializer.read(valueDeserializer) as TextTimerController)
        }
        const controller_result : TextTimerController | undefined = controller_buf
        let value : TextTimerOptions = ({isCountDown: isCountDown_result, controller: controller_result} as TextTimerOptions)
        return value
    }
}

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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, ShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ResourceColor, Length, ResourceStr } from "./units"
import { Color, FontStyle, FontWeight } from "./enums"
import { ContentModifier, AttributeModifier, hookTextTimerContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_ctor()
        return retval
    }
    constructor() {
        this(TextTimerController.ctor())
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            TextTimerOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextTimerInterface_setTextTimerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    formatAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_format(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | ResourceStr | undefined): void {
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
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as ResourceStr
                let value_value_2_type : int32 = RuntimeType.UNDEFINED
                value_value_2_type = runtimeType(value_value_2)
                if (RuntimeType.STRING == value_value_2_type) {
                    thisSerializer.writeInt8(0)
                    const value_value_2_0  = value_value_2 as string
                    thisSerializer.writeString(value_value_2_0)
                }
                else if (RuntimeType.OBJECT == value_value_2_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_2_1  = value_value_2 as Resource
                    Resource_serializer.write(thisSerializer, value_value_2_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: ResourceStr | undefined): void {
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTimerAttribute(value: ((utc: number,elapsedTime: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_onTimer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_textShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier<TextTimerConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    count?: number;
    controller?: TextTimerController;
}
export interface TextTimerAttribute extends CommonMethod {
    format(value: string | undefined): this
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: Length | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontWeight(value: number | FontWeight | ResourceStr | undefined): this
    fontFamily(value: ResourceStr | undefined): this
    onTimer(value: ((utc: number,elapsedTime: number) => void) | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this
    contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this
    attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this
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
            this.getPeer()?.formatAttribute(value_casted)
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
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | ResourceStr | undefined)
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
    public onTimer(value: ((utc: number,elapsedTime: number) => void) | undefined): this {
        if (this.checkPriority("onTimer")) {
            const value_casted = value as (((utc: number,elapsedTime: number) => void) | undefined)
            this.getPeer()?.onTimerAttribute(value_casted)
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
    public contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookTextTimerContentModifier(this, value)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("TextTimerImpl")
export function TextTimer(
    options?: TextTimerOptions | undefined,
    @memo
    content_?: () => void,
): TextTimerAttribute {
    throw new Error("Not implemented")
}

@memo
export function TextTimerImpl(
    @memo
    style: ((attributes: TextTimerAttribute) => void) | undefined,
    options?: TextTimerOptions | undefined,
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
        valueSerializer.writeInt8(value_isCountDown_type)
        if ((RuntimeType.UNDEFINED) != (value_isCountDown_type)) {
            const value_isCountDown_value  = value_isCountDown!
            valueSerializer.writeBoolean(value_isCountDown_value)
        }
        const value_count  = value.count
        let value_count_type : int32 = RuntimeType.UNDEFINED
        value_count_type = runtimeType(value_count)
        valueSerializer.writeInt8(value_count_type)
        if ((RuntimeType.UNDEFINED) != (value_count_type)) {
            const value_count_value  = value_count!
            valueSerializer.writeNumber(value_count_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8(value_controller_type)
        if ((RuntimeType.UNDEFINED) != (value_controller_type)) {
            const value_controller_value  = value_controller!
            TextTimerController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): TextTimerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isCountDown_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let isCountDown_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (isCountDown_buf_runtimeType))
        {
            isCountDown_buf = valueDeserializer.readBoolean()
        }
        const isCountDown_result : boolean | undefined = isCountDown_buf
        const count_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let count_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (count_buf_runtimeType))
        {
            count_buf = (valueDeserializer.readNumber() as number)
        }
        const count_result : number | undefined = count_buf
        const controller_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let controller_buf : TextTimerController | undefined
        if ((RuntimeType.UNDEFINED) != (controller_buf_runtimeType))
        {
            controller_buf = (TextTimerController_serializer.read(valueDeserializer) as TextTimerController)
        }
        const controller_result : TextTimerController | undefined = controller_buf
        let value : TextTimerOptions = ({isCountDown: isCountDown_result, count: count_result, controller: controller_result} as TextTimerOptions)
        return value
    }
}

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
import { ResourceColor, Length, ResourceStr } from "./units"
import { FontStyle, FontWeight, Color } from "./enums"
import { TextTimerAttribute_onTimer_event_type } from "./type-replacements"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Resource } from "global.resource"
import { NodeAttach, remember } from "@koalaui/runtime"

export class TextTimerControllerInternal {
    public static fromPtr(ptr: KPointer): TextTimerController {
        const obj : TextTimerController = new TextTimerController()
        obj.peer = new Finalizable(ptr, TextTimerController.getFinalizer())
        return obj
    }
}
export class TextTimerController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_texttimercontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextTimerController.ctor_texttimercontroller()
        this.peer = new Finalizable(ctorPtr, TextTimerController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextTimerController_getFinalizer()
    }
    public start(): void {
        this.start_serialize();
        return;
    }
    public pause(): void {
        this.pause_serialize();
        return;
    }
    public reset(): void {
        this.reset_serialize();
        return;
    }
    private start_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_start(this.peer!.ptr)
        return retval
    }
    private pause_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_pause(this.peer!.ptr)
        return retval
    }
    private reset_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_reset(this.peer!.ptr)
        return retval
    }
}
export class ArkTextTimerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTextTimerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextTimer_construct(peerId, flags)
        const _peer  = new ArkTextTimerPeer(_peerPtr, peerId, "TextTimer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextTimerOptionsAttribute(options?: TextTimerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextTimerOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextTimerInterface_setTextTimerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_format(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTimerAttribute(value: ((utc: int64,elapsedTime: int64) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_onTimer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_textShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextTimerConfiguration extends CommonConfiguration {
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
export type TextTimerInterface = (options?: TextTimerOptions) => TextTimerAttribute;
export interface TextTimerAttribute extends CommonMethod {
    format(value: string | undefined): this
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: Length | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    fontFamily(value: ResourceStr | undefined): this
    onTimer(value: ((utc: int64,elapsedTime: int64) => void) | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this
    contentModifier(value: ContentModifier | undefined): this
}
export class ArkTextTimerStyle extends ArkCommonMethodStyle implements TextTimerAttribute {
    format_value?: string | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: ResourceStr | undefined
    onTimer_value?: ((utc: int64,elapsedTime: int64) => void) | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    contentModifier_value?: ContentModifier | undefined
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
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        return this
    }
    public onTimer(value: ((utc: int64,elapsedTime: int64) => void) | undefined): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        return this
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
    public onTimer(value: ((utc: int64,elapsedTime: int64) => void) | undefined): this {
        if (this.checkPriority("onTimer")) {
            const value_casted = value as (((utc: int64,elapsedTime: int64) => void) | undefined)
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
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
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
export function TextTimer(
    /** @memo */
    style: ((attributes: TextTimerAttribute) => void) | undefined,
    options?: TextTimerOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkTextTimerComponent()
    })
    NodeAttach<ArkTextTimerPeer>((): ArkTextTimerPeer => ArkTextTimerPeer.create(receiver), (_: ArkTextTimerPeer) => {
        receiver.setTextTimerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor, Length } from "./units"
import { Color, FontWeight, MarqueeUpdateStrategy } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMarqueePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMarqueePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Marquee_construct(peerId, flags)
        const _peer  = new ArkMarqueePeer(_peerPtr, peerId, "Marquee", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMarqueeOptionsAttribute(options: MarqueeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MarqueeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._MarqueeInterface_setMarqueeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowScaleAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setAllowScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarqueeUpdateStrategyAttribute(value: MarqueeUpdateStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as MarqueeUpdateStrategy)
            thisSerializer.writeInt32(TypeChecker.MarqueeUpdateStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setMarqueeUpdateStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBounceAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setOnBounce(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface MarqueeOptions {
    start: boolean;
    step?: number;
    loop?: number;
    fromStart?: boolean;
    src: string;
}
export interface MarqueeAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: Length | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    allowScale(value: boolean | undefined): this {
        throw new Error("Unimplemented method allowScale")
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    fontFamily(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        throw new Error("Unimplemented method marqueeUpdateStrategy")
    }
    onStart(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onStart")
    }
    onBounce(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onBounce")
    }
    onFinish(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onFinish")
    }
    attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkMarqueeStyle extends ArkCommonMethodStyle implements MarqueeAttribute {
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    allowScale_value?: boolean | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: string | Resource | undefined
    marqueeUpdateStrategy_value?: MarqueeUpdateStrategy | undefined
    onStart_value?: (() => void) | undefined
    onBounce_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
    attributeModifier_value?: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: Length | undefined): this {
        return this
    }
    public allowScale(value: boolean | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        return this
    }
    public onBounce(value: (() => void) | undefined): this {
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: MarqueeAttribute): void {
        super.apply(target)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.allowScale_value !== undefined)
            target.allowScale(this.allowScale_value!)
        if (this.fontWeight_value !== undefined)
            target.fontWeight(this.fontWeight_value!)
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.marqueeUpdateStrategy_value !== undefined)
            target.marqueeUpdateStrategy(this.marqueeUpdateStrategy_value!)
        if (this.onStart_value !== undefined)
            target.onStart(this.onStart_value!)
        if (this.onBounce_value !== undefined)
            target.onBounce(this.onBounce_value!)
        if (this.onFinish_value !== undefined)
            target.onFinish(this.onFinish_value!)
    }
}

export class ArkMarqueeComponent extends ArkCommonMethodComponent implements MarqueeAttribute {
    getPeer(): ArkMarqueePeer {
        return (this.peer as ArkMarqueePeer)
    }
    public setMarqueeOptions(options: MarqueeOptions): this {
        if (this.checkPriority("setMarqueeOptions")) {
            const options_casted = options as (MarqueeOptions)
            this.getPeer()?.setMarqueeOptionsAttribute(options_casted)
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
    public allowScale(value: boolean | undefined): this {
        if (this.checkPriority("allowScale")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAllowScaleAttribute(value_casted)
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
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        if (this.checkPriority("marqueeUpdateStrategy")) {
            const value_casted = value as (MarqueeUpdateStrategy | undefined)
            this.getPeer()?.setMarqueeUpdateStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onBounce(value: (() => void) | undefined): this {
        if (this.checkPriority("onBounce")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnBounceAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withMarqueeStyle(receiver: MarqueeAttribute, modifier: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkMarqueeStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Marquee")
// export function Marquee(
//     options: MarqueeOptions,
//     @memo
//     content_?: () => void,
// ): MarqueeAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Marquee(
    @memo
    style: ((attributes: MarqueeAttribute) => void) | undefined,
    options: MarqueeOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMarqueeComponent>((): ArkMarqueeComponent => {
        return new ArkMarqueeComponent()
    })
    NodeAttach<ArkMarqueePeer>((): ArkMarqueePeer => ArkMarqueePeer.create(receiver), (_: ArkMarqueePeer): void => {
        receiver.setMarqueeOptions(options)
        style?.(receiver)
        withMarqueeStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkMarqueeSet extends ArkCommonMethodSet implements MarqueeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: Length | undefined
    _allowScale_flag?: boolean
    _allowScale0_value?: boolean | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | string | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: string | Resource | undefined
    _marqueeUpdateStrategy_flag?: boolean
    _marqueeUpdateStrategy0_value?: MarqueeUpdateStrategy | undefined
    _onStart_flag?: boolean
    _onStart0_value?: (() => void) | undefined
    _onBounce_flag?: boolean
    _onBounce0_value?: (() => void) | undefined
    _onFinish_flag?: boolean
    _onFinish0_value?: (() => void) | undefined
    applyModifierPatch(component: MarqueeAttribute): void {
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as Length | undefined))
        if (this._allowScale_flag)
            component.allowScale((this._allowScale0_value as boolean | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | string | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as string | Resource | undefined))
        if (this._marqueeUpdateStrategy_flag)
            component.marqueeUpdateStrategy((this._marqueeUpdateStrategy0_value as MarqueeUpdateStrategy | undefined))
        if (this._onStart_flag)
            component.onStart((this._onStart0_value as (() => void) | undefined))
        if (this._onBounce_flag)
            component.onBounce((this._onBounce0_value as (() => void) | undefined))
        if (this._onFinish_flag)
            component.onFinish((this._onFinish0_value as (() => void) | undefined))
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
    public allowScale(value: boolean | undefined): this {
        this._allowScale_flag = true
        this._allowScale0_value = value
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        this._marqueeUpdateStrategy_flag = true
        this._marqueeUpdateStrategy0_value = value
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        this._onStart_flag = true
        this._onStart0_value = value
        return this
    }
    public onBounce(value: (() => void) | undefined): this {
        this._onBounce_flag = true
        this._onBounce0_value = value
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        this._onFinish_flag = true
        this._onFinish0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class MarqueeOptions_serializer {
    public static write(buffer: SerializerBase, value: MarqueeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        valueSerializer.writeBoolean(value_start)
        const value_step  = value.step
        let value_step_type : int32 = RuntimeType.UNDEFINED
        value_step_type = runtimeType(value_step)
        valueSerializer.writeInt8((value_step_type).toChar())
        if ((value_step_type) != (RuntimeType.UNDEFINED)) {
            const value_step_value  = value_step!
            valueSerializer.writeNumber(value_step_value)
        }
        const value_loop  = value.loop
        let value_loop_type : int32 = RuntimeType.UNDEFINED
        value_loop_type = runtimeType(value_loop)
        valueSerializer.writeInt8((value_loop_type).toChar())
        if ((value_loop_type) != (RuntimeType.UNDEFINED)) {
            const value_loop_value  = value_loop!
            valueSerializer.writeNumber(value_loop_value)
        }
        const value_fromStart  = value.fromStart
        let value_fromStart_type : int32 = RuntimeType.UNDEFINED
        value_fromStart_type = runtimeType(value_fromStart)
        valueSerializer.writeInt8((value_fromStart_type).toChar())
        if ((value_fromStart_type) != (RuntimeType.UNDEFINED)) {
            const value_fromStart_value  = value_fromStart!
            valueSerializer.writeBoolean(value_fromStart_value)
        }
        const value_src  = value.src
        valueSerializer.writeString(value_src)
    }
    public static read(buffer: DeserializerBase): MarqueeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_result : boolean = valueDeserializer.readBoolean()
        const step_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let step_buf : number | undefined
        if ((step_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            step_buf = (valueDeserializer.readNumber() as number)
        }
        const step_result : number | undefined = step_buf
        const loop_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let loop_buf : number | undefined
        if ((loop_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            loop_buf = (valueDeserializer.readNumber() as number)
        }
        const loop_result : number | undefined = loop_buf
        const fromStart_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fromStart_buf : boolean | undefined
        if ((fromStart_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fromStart_buf = valueDeserializer.readBoolean()
        }
        const fromStart_result : boolean | undefined = fromStart_buf
        const src_result : string = (valueDeserializer.readString() as string)
        let value : MarqueeOptions = ({start: start_result, step: step_result, loop: loop_result, fromStart: fromStart_result, src: src_result} as MarqueeOptions)
        return value
    }
}

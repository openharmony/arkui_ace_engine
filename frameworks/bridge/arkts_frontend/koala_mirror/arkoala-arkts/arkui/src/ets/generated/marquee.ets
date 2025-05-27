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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, Length } from "./units"
import { FontWeight, MarqueeUpdateStrategy, Color } from "./enums"
import { Resource } from "./resource"
import { Callback_Void } from "./ability_component"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMarqueeOptions(options)
        ArkUIGeneratedNativeModule._MarqueeInterface_setMarqueeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    allowScaleAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._MarqueeAttribute_allowScale(this.peer.ptr, value ? 1 : 0)
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
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
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    marqueeUpdateStrategyAttribute(value: MarqueeUpdateStrategy): void {
        ArkUIGeneratedNativeModule._MarqueeAttribute_marqueeUpdateStrategy(this.peer.ptr, TypeChecker.MarqueeUpdateStrategy_ToNumeric(value))
    }
    onStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._MarqueeAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBounceAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._MarqueeAttribute_onBounce(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._MarqueeAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    fontColor(value: ResourceColor): this
    fontSize(value: Length): this
    allowScale(value: boolean): this
    fontWeight(value: number | FontWeight | string): this
    fontFamily(value: string | Resource): this
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy): this
    onStart(value: (() => void)): this
    onBounce(value: (() => void)): this
    onFinish(value: (() => void)): this
    attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIMarqueeAttribute extends UICommonMethod {
    @memo
    fontColor(value: ResourceColor): this
    @memo
    fontSize(value: Length): this
    @memo
    allowScale(value: boolean): this
    @memo
    fontWeight(value: number | FontWeight | string): this
    @memo
    fontFamily(value: string | Resource): this
    @memo
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy): this
    @memo
    onStart(value: (() => void)): this
    @memo
    onBounce(value: (() => void)): this
    @memo
    onFinish(value: (() => void)): this
    @memo
    attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkMarqueeStyle extends ArkCommonMethodStyle implements MarqueeAttribute {
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    allowScale_value?: boolean
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: string | Resource
    marqueeUpdateStrategy_value?: MarqueeUpdateStrategy
    onStart_value?: (() => void)
    onBounce_value?: (() => void)
    onFinish_value?: (() => void)
    public fontColor(value: ResourceColor): this {
        return this
    }
    public fontSize(value: Length): this {
        return this
    }
    public allowScale(value: boolean): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string): this {
        return this
    }
    public fontFamily(value: string | Resource): this {
        return this
    }
    public marqueeUpdateStrategy(value: MarqueeUpdateStrategy): this {
        return this
    }
    public onStart(value: (() => void)): this {
        return this
    }
    public onBounce(value: (() => void)): this {
        return this
    }
    public onFinish(value: (() => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkMarqueeComponent extends ArkCommonMethodComponent implements UIMarqueeAttribute {
    getPeer(): ArkMarqueePeer {
        return (this.peer as ArkMarqueePeer)
    }
    @memo
    public setMarqueeOptions(options: MarqueeOptions): this {
        if (this.checkPriority("setMarqueeOptions")) {
            const options_casted = options as (MarqueeOptions)
            this.getPeer()?.setMarqueeOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public allowScale(value: boolean): this {
        if (this.checkPriority("allowScale")) {
            const value_casted = value as (boolean)
            this.getPeer()?.allowScaleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontFamily(value: string | Resource): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public marqueeUpdateStrategy(value: MarqueeUpdateStrategy): this {
        if (this.checkPriority("marqueeUpdateStrategy")) {
            const value_casted = value as (MarqueeUpdateStrategy)
            this.getPeer()?.marqueeUpdateStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onStart(value: (() => void)): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onBounce(value: (() => void)): this {
        if (this.checkPriority("onBounce")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onBounceAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFinish(value: (() => void)): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Marquee")
export function Marquee(
    options: MarqueeOptions,
    @memo
    content_?: () => void,
): MarqueeAttribute {
    throw new Error("Not implemented")
}

@memo
export function Marquee(
    @memo
    style: ((attributes: UIMarqueeAttribute) => void) | undefined,
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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

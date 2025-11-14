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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length } from "./units"
import { Color, FontWeight, MarqueeUpdateStrategy } from "./enums"
import { Resource } from "global.resource"
import { AttributeModifier, hookMarqueeAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { MarqueeModifier } from "./../MarqueeModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkMarqueePeer extends ArkCommonMethodPeer {
    attributeSet?: MarqueeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMarqueePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Marquee_construct(peerId, flags)
        const _peer  = new ArkMarqueePeer(_peerPtr, peerId, 'Marquee', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowScaleAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setAllowScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(valueTmpValueForIdx1.valueOf())
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarqueeUpdateStrategyAttribute(value: MarqueeUpdateStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as MarqueeUpdateStrategy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setMarqueeUpdateStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBounceAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setOnBounce(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MarqueeAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface MarqueeOptions {
    start: boolean | undefined;
    step?: double;
    loop?: int32;
    fromStart?: boolean;
    src: string | undefined;
}
export interface MarqueeAttribute extends CommonMethod {
    setMarqueeOptions(options: MarqueeOptions): this {
        throw new Error("Unimplemented method setMarqueeOptions")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: Length | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    allowScale(value: boolean | undefined): this {
        throw new Error("Unimplemented method allowScale")
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
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
    fontWeight_value?: int32 | FontWeight | string | undefined
    fontFamily_value?: string | Resource | undefined
    marqueeUpdateStrategy_value?: MarqueeUpdateStrategy | undefined
    onStart_value?: (() => void) | undefined
    onBounce_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
    attributeModifier_value?: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined
    setMarqueeOptions(options: MarqueeOptions): this {
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        return this
    }
    fontSize(value: Length | undefined): this {
        return this
    }
    allowScale(value: boolean | undefined): this {
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        return this
    }
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        return this
    }
    onStart(value: (() => void) | undefined): this {
        return this
    }
    onBounce(value: (() => void) | undefined): this {
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkMarqueeComponent extends ArkCommonMethodComponent implements MarqueeAttribute {
    getPeer(): ArkMarqueePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkMarqueePeer)
    }
    public setMarqueeOptions(options: MarqueeOptions): this {
        if (this.checkPriority("setMarqueeOptions")) {
            const options_casted = options as (MarqueeOptions)
            this.getPeer()?.setMarqueeOptionsAttribute(options_casted)
            this.applyOptionsFinish('MarqueeAttribute');
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
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
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
        ModifierStateManager.INSTANCE.scope(() => {
            hookMarqueeAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function MarqueeImpl(
    @memo
    style: ((attributes: MarqueeAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMarqueeComponent>((): ArkMarqueeComponent => {
        return new ArkMarqueeComponent()
    })
    NodeAttach<ArkMarqueePeer>((): ArkMarqueePeer => ArkMarqueePeer.create(receiver), (peer: ArkMarqueePeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class MarqueeOptions_serializer {
    public static write(buffer: SerializerBase, value: MarqueeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeBoolean(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStep  = value.step
        if (valueHolderForStep !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStepTmpValue  = valueHolderForStep!
            valueSerializer.writeFloat64(valueHolderForStepTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLoop  = value.loop
        if (valueHolderForLoop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLoopTmpValue  = valueHolderForLoop!
            valueSerializer.writeInt32(valueHolderForLoopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFromStart  = value.fromStart
        if (valueHolderForFromStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFromStartTmpValue  = valueHolderForFromStart!
            valueSerializer.writeBoolean(valueHolderForFromStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcTmpValue  = valueHolderForSrc!
            valueSerializer.writeString(valueHolderForSrcTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MarqueeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : boolean | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readBoolean()
        }
        const startTmpResult : boolean | undefined = startTmpBuf
        const stepTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stepTmpBuf : double | undefined = undefined
        if ((stepTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stepTmpBuf = valueDeserializer.readFloat64()
        }
        const stepTmpResult : double | undefined = stepTmpBuf
        const loopTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let loopTmpBuf : int32 | undefined = undefined
        if ((loopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            loopTmpBuf = valueDeserializer.readInt32()
        }
        const loopTmpResult : int32 | undefined = loopTmpBuf
        const fromStartTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fromStartTmpBuf : boolean | undefined = undefined
        if ((fromStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fromStartTmpBuf = valueDeserializer.readBoolean()
        }
        const fromStartTmpResult : boolean | undefined = fromStartTmpBuf
        const srcTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let srcTmpBuf : string | undefined = undefined
        if ((srcTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        }
        const srcTmpResult : string | undefined = srcTmpBuf
        let value : MarqueeOptions = ({start: startTmpResult, step: stepTmpResult, loop: loopTmpResult, fromStart: fromStartTmpResult, src: srcTmpResult} as MarqueeOptions)
        return value
    }
}
